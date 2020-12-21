#include "level2.h"
#include "expression.h"
#include "l2dragwidget.h"
#include "ui_level2.h"
#include <QLabel>
#include <QTimer>
#include <iostream>
#include <string>

#include "scorecontext.h"
#include <QTime>

#include <Box2D/Box2D.h>
#include <QMessageBox>

Level2::Level2(QWidget *parent) : QWidget(parent), ui(new Ui::Level2)
{
	ui->setupUi(this);
	QPalette pal = palette();
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Score = 0;

	drag = new L2DragWidget(this);
	ui->selectionDraggables->addWidget(drag);

	currentLetterSelection = -1;
	visited = 0;

	/* Dynamically add pixmap at runtime because Qt is having trouble doing
	 * so. */
	p = new QLabel(ui->letterP);
	QPixmap mapP(":/alden/images/P.png");
	p->setPixmap(mapP.scaled(100, 100, Qt::KeepAspectRatio));
	p->move(80, 100);
	p->show();
	p->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	e = new QLabel(ui->letterE);
	QPixmap mapE(":/alden/images/E.png");
	e->setPixmap(mapE.scaled(100, 100, Qt::KeepAspectRatio));
	e->move(80, 100);
	e->show();
	e->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	m = new QLabel(ui->letterM);
	QPixmap mapM(":/alden/images/M.png");
	m->setPixmap(mapM.scaled(100, 100, Qt::KeepAspectRatio));
	m->move(70, 100);
	m->show();
	m->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	d = new QLabel(ui->letterD);
	QPixmap mapD(":/alden/images/D.png");
	d->setPixmap(mapD.scaled(100, 100, Qt::KeepAspectRatio));
	d->move(80, 100);
	d->show();
	d->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	a = new QLabel(ui->letterA);
	QPixmap mapA(":/alden/images/A.png");
	a->setPixmap(mapA.scaled(100, 100, Qt::KeepAspectRatio));
	a->move(80, 100);
	a->show();
	a->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	s = new QLabel(ui->letterS);
	QPixmap mapS(":/alden/images/S.png");
	s->setPixmap(mapS.scaled(100, 100, Qt::KeepAspectRatio));
	s->move(80, 100);
	s->show();
	s->setAttribute(Qt::WA_DeleteOnClose); // Auto delete so I don't have to

	/* We do this in the cpp file so it can  start greyed out*/
	QPixmap pixmap(":/Pictures/startgameorange.png");
	QIcon ButtonIcon(pixmap);
	this->ui->quizButton->setIcon(ButtonIcon);
	this->ui->quizButton->setIconSize(pixmap.rect().size());

	connect(ui->backP, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);
	connect(ui->backE, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);
	connect(ui->backM, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);
	connect(ui->backD, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);
	connect(ui->backA, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);
	connect(ui->backS, &QPushButton::pressed, this,
		&Level2::load_selectLetterMenu);

	connect(ui->quizButton, &QPushButton::pressed, this,
		&Level2::load_quizMenu);
	connect(ui->answerQ,
		static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
		this, &Level2::quiz_checkAnswer);

	ui->stackedWidget->setCurrentWidget(ui->selectLetter);
}

Level2::~Level2()
{
	delete ui;
	delete drag;
	delete p;
	delete e;
	delete m;
	delete d;
	delete a;
	delete s;
}

void Level2::quiz_showNextQuestion()
{
	std::string question = randomCheckedIntegerExpression(quiz_answer);
	ui->questionQ->setText(QString::fromStdString(question));
	ui->answerQ->setValue(0);

	QPalette pal = palette();
	pal.setColor(QPalette::Base, Qt::yellow);
	ui->answerQ->setPalette(pal);
}

void Level2::quiz_correctAnswer()
{
	this->Game->DefeatEnemy();
	this->Score += 50;
	this->ui->score->display((double)this->Score);
	ScoreContext::SetScore(1, this->Score);
	quiz_showNextQuestion();
}

void Level2::quiz_wrongAnswer() { this->Game->AdvanceEnemy(); }

void Level2::quiz_checkAnswer(int i)
{
	if (i == quiz_answer)
	{
		quiz_correctAnswer();
	}
	else
	{
		quiz_wrongAnswer();
	}
	this->Game->repaint();
}

void Level2::load_quizMenu()
{
	ui->stackedWidget->setCurrentWidget(ui->quiz);
	this->Game = new L2InvaderGame(this->ui->scrollArea);
	this->ui->scrollArea->setMinimumSize(this->Game->minimumSize());
	this->ui->scrollArea->setWidget(this->Game);
	this->Game->setMinimumSize(this->ui->scrollArea->size());
	this->Game->show();
	this->Game->connect(
	    this->Game, &L2InvaderGame::GameOver, this, [this]() {
		    QMessageBox::information(
			this, "Game Over",
			QString("Your score was: %1.").arg(this->Score));
		    ScoreContext::SetScore(1, this->Score);
		    this->Score = 0;
		    this->Game->Reset();
		    this->ui->score->display(0);
		    ui->stackedWidget->setCurrentWidget(ui->selectLetter);
		    emit returnToSelectClicked();
	    });

	this->Game->connect(
	    this->Game, &L2InvaderGame::Victory, this, [this]() {
		    this->Score += 1200;
		    QMessageBox::information(
			this, "You Win!",
			QString("Your score was: %1.").arg(this->Score));
		    ScoreContext::SetScore(1, this->Score);
		    this->Score = 0;
		    this->Game->Reset();
		    this->ui->score->display(0);
		    ui->stackedWidget->setCurrentWidget(ui->selectLetter);
		    emit returnToSelectClicked();
	    });
	quiz_showNextQuestion();
}

void Level2::load_letterMenu(int selection)
{
	currentLetterSelection = selection;
	switch (selection)
	{
	case 0:
		visited |= 0x1;
		ui->stackedWidget->setCurrentWidget(ui->letterP);
		ui->exampleP1_Ans->hide();
		ui->exampleP2_Ans->hide();
		updateTimer(ui->timerP, currentLetterSelection, 1500);
		break;
	case 1:
		visited |= 0x2;
		ui->stackedWidget->setCurrentWidget(ui->letterE);
		ui->exampleE1_Ans->hide();
		ui->exampleE2_Ans->hide();
		updateTimer(ui->timerE, currentLetterSelection, 1500);
		break;
	case 2:
		visited |= 0x4;
		ui->stackedWidget->setCurrentWidget(ui->letterM);
		ui->exampleM1_Ans->hide();
		ui->exampleM2_Ans->hide();
		updateTimer(ui->timerM, currentLetterSelection, 1500);
		break;
	case 3:
		visited |= 0x8;
		ui->stackedWidget->setCurrentWidget(ui->letterD);
		ui->exampleD1_Ans->hide();
		ui->exampleD2_Ans->hide();
		updateTimer(ui->timerD, currentLetterSelection, 1500);
		break;
	case 4:
		visited |= 0x10;
		ui->stackedWidget->setCurrentWidget(ui->letterA);
		ui->exampleA1_Ans->hide();
		ui->exampleA2_Ans->hide();
		updateTimer(ui->timerA, currentLetterSelection, 1500);
		break;
	case 5:
		visited |= 0x20;
		ui->stackedWidget->setCurrentWidget(ui->letterS);
		ui->exampleS1_Ans->hide();
		ui->exampleS2_Ans->hide();
		updateTimer(ui->timerS, currentLetterSelection, 1500);
		break;
	}

	if (visited == 0x3F)
	{
		ui->quizButton->setEnabled(true);
		ui->quizButton->setCursor(Qt::ArrowCursor);
	}
}

void Level2::updateTimer(QSlider *slider, int letter, int update)
{
	if (currentLetterSelection != letter)
		return;
	if (update == 0)
	{
		showAnswers(letter);
		// Don't return here since we don't want slider manipulation.
	}
	slider->setValue(update);
	QTimer::singleShot(10, [this, slider, letter, update] {
		this->updateTimer(slider, letter, update - 2);
	});
}

void Level2::showAnswers(int letter)
{
	switch (letter)
	{
	case 0:
		ui->exampleP1_Ans->show();
		ui->exampleP2_Ans->show();
		break;
	case 1:
		ui->exampleE1_Ans->show();
		ui->exampleE2_Ans->show();
		break;
	case 2:
		ui->exampleM1_Ans->show();
		ui->exampleM2_Ans->show();
		break;
	case 3:
		ui->exampleD1_Ans->show();
		ui->exampleD2_Ans->show();
		break;
	case 4:
		ui->exampleA1_Ans->show();
		ui->exampleA2_Ans->show();
		break;
	case 5:
		ui->exampleS1_Ans->show();
		ui->exampleS2_Ans->show();
		break;
	}
}

void Level2::load_selectLetterMenu()
{
	currentLetterSelection = -1;
	ui->stackedWidget->setCurrentWidget(ui->selectLetter);
}

void Level2::on_levelSelectButton_clicked() { emit returnToSelectClicked(); }

void Level2::on_levelSelectButton_2_clicked() { emit returnToSelectClicked(); }
