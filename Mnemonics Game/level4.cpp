#include "level4.h"
#include "scorecontext.h"
#include "ui_level4.h"

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QPen>

#include <QTimer>

#include <QRandomGenerator>
#include <iostream>
#include <vector>

Level4::Level4(QWidget *parent) : QWidget(parent), ui(new Ui::Level4)
{
	ui->setupUi(this);

	/* Setup QGraphicsScene */
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	/* Setup Box2D World */
	this->world = new b2World(b2Vec2(0.0f, -8.8f));
	this->scene = new QGraphicsScene();
	this->scene->setSceneRect(0, 0, ui->graphicsView->width(),
				  ui->graphicsView->height());
	ui->graphicsView->setScene(this->scene);
	this->ground = new QGraphicsRectItem();
	this->scene->addItem(this->ground);
	this->ground->setRect(0, 0, this->scene->width(), 25);
	this->ground->setPos(0, 450);
	this->ground->setBrush(Qt::cyan);

	b2PolygonShape groundBox;
	groundBox.SetAsBox((this->width() / 100.0f) / 2, (25.0f / 100.0f) / 2);
	b2FixtureDef def;
	def.shape = &groundBox;
	def.density = 1.0f;
	def.friction = 1.0f;
	def.restitution = 0.6f;

	b2BodyDef groundBody;
	groundBody.type = b2_staticBody;
	groundBody.position.Set(
	    (this->scene->width() / 100.0f) / 2.0f,
	    -(this->scene->height() / 100.0f) +
		((this->ground->boundingRect().height() + 1) / 100.0f) * 4);
	b2Body *body = this->world->CreateBody(&groundBody);
	body->CreateFixture(&def);
	this->startedWorldUpdates = false;
	this->squares.clear();
	for (int i = 0; i < 7; i++)
	{
		this->squares.append(nullptr);
	}
	winTheGame = false;

	connect(ui->startButton, &QPushButton::pressed, this,
		&Level4::showintroduction);
	connect(ui->nextButton, &QPushButton::pressed, this,
		&Level4::showintroduction);
	connect(ui->goTotutorialButton, &QPushButton::pressed, this,
		&Level4::showTutorial);

	connect(ui->beginGameButton, &QPushButton::pressed, this,
		&Level4::showGameplay);
	connect(ui->proceedButton, &QPushButton::pressed, this,
		&Level4::updateGame);
	connect(ui->returnToMenuButton, &QPushButton::pressed, this,
		&Level4::returnToStartScreen);
	connect(ui->nextStepButton, &QPushButton::pressed, this,
		&Level4::showinstructions);
	connect(ui->nextButton, &QPushButton::pressed, this,
		&Level4::showintroduction);

	//    connect(ui->seeThePieButton, &QPushButton::pressed, this,
	//        &Level4::showPieShape);
	connect(ui->endGameButton, &QPushButton::pressed, this,
		&Level4::endGame);
	connect(ui->rightAnsButton, &QPushButton::pressed, this,
		&Level4::showWinMessage);
	connect(ui->wrongAnsButton, &QPushButton::pressed, this,
		&Level4::showLoseMessage);

	ui->introduction->setVisible(false);
	ui->task->setVisible(false);
	ui->result1->setVisible(false);
	ui->result2->setVisible(false);

	ui->nextButton->setVisible(false);
	ui->goTotutorialButton->setVisible(false);

	centerX = ui->stackedWidget->width() / 2;
	centerY = ui->stackedWidget->height() / 2;

	ui->stackedWidget->setCurrentIndex(0);
	ui->proceedButton->setEnabled(false);

	ui->endGameButton->setVisible(false);
	//	ui->seeThePieButton->setVisible(false);

	int UIWidth = ui->stackedWidget->width();
	int UIHeight = ui->stackedWidget->height();

	int x = 3 * UIWidth / 10;
	int y = 3 * UIHeight / 10;

	int squareLength = 150;
	int sideLength = 50;
	ui->pushButton->setVisible(false);
	ui->gameTitle->setStyleSheet(QString("color: orange"));
	QuadSquare = QRect(x, y, squareLength, squareLength);
	UpperLinearRectangle =
	    QRect(x + squareLength, y, sideLength, squareLength);
	LowerLinearRectangle =
	    QRect(x, y + squareLength, squareLength, sideLength);
	ConstSquare =
	    QRect(x + squareLength, y + squareLength, sideLength, sideLength);

	showPie = false;

	maxRound = 10;
	tutorialStep = 0;
	introductionStep = 0;

	ui->beginGameButton->setVisible(false);
	ui->nextStepButton->setVisible(true);
	ui->message->setAlignment(Qt::AlignCenter);

	filled = false;

	linearConst = 1;
	round = 0;

	// ui->label->setStyleSheet(QString("color: red"));

	seed = 0;

	random.seed(seed);

	ui->tutorialheaderLabel->setStyleSheet(QString("color: yellow"));
	ui->instructionLabel->setStyleSheet(
	    QString("background-color: black; color: white;"));

	ui->endLabel->setStyleSheet(QString("color:yellow"));
	// QRandomGenerator random;

	// linearConst = (int)(random.bounded(10));

	/* background 1 */
	ui->backgroundText->setAlignment(Qt::AlignCenter);
	ui->backgroundText->setWordWrap(true);
	/* Setup dude for facts page */
	QPixmap dude(":/images/ImagesLevel6/lean.png");
	int w = ui->img->width();
	int h = ui->img->height();
	ui->img->setMinimumSize(1, 1);
	ui->img->setPixmap(dude.scaled(w, h, Qt::KeepAspectRatio));

	/* background 2 */
	ui->backgroundText_2->setAlignment(Qt::AlignCenter);
	ui->backgroundText_2->setWordWrap(true);
	/* Setup img for facts page */
	QPixmap img2(":/images/complete_sqare/1.png");
	int w2 = ui->img_2->width();
	int h2 = ui->img_2->height();
	ui->img_2->setMinimumSize(1, 1);
	ui->img_2->setPixmap(img2.scaled(w2, h2, Qt::KeepAspectRatio));

	/* background 3 */
	ui->backgroundText_3->setAlignment(Qt::AlignCenter);
	ui->backgroundText_3->setWordWrap(true);
	/* Setup img for facts page */
	QPixmap img3(":/images/complete_sqare/2.png");
	int w3 = ui->img_3->width();
	int h3 = ui->img_3->height();
	ui->img_3->setMinimumSize(1, 1);
	ui->img_3->setPixmap(img3.scaled(w3, h3, Qt::KeepAspectRatio));

	/* background 4 */
	ui->backgroundText_4->setAlignment(Qt::AlignCenter);
	ui->backgroundText_4->setWordWrap(true);
	/* Setup img for facts page */
	QPixmap img4(":/images/complete_sqare/3.png");
	int w4 = ui->img_4->width();
	int h4 = ui->img_4->height();
	ui->img_4->setMinimumSize(1, 1);
	ui->img_4->setPixmap(img4.scaled(w4, h4, Qt::KeepAspectRatio));

	/* background 5 */
	ui->backgroundText_5->setAlignment(Qt::AlignCenter);
	ui->backgroundText_5->setWordWrap(true);
	/* Setup img for facts page */
	QPixmap img5(":/images/complete_sqare/4.png");
	int w5 = ui->img_5->width();
	int h5 = ui->img_5->height();
	ui->img_5->setMinimumSize(1, 1);
	ui->img_5->setPixmap(img5.scaled(w5, h5, Qt::KeepAspectRatio));

	/* background 6 */
	ui->backgroundText_6->setAlignment(Qt::AlignCenter);
	ui->backgroundText_6->setWordWrap(true);
	/* Setup img for facts page */
	QPixmap img6(":/images/complete_sqare/5.png");
	int w6 = ui->img_6->width();
	int h6 = ui->img_6->height();
	ui->img_6->setMinimumSize(1, 1);
	ui->img_6->setPixmap(img6.scaled(w6, h6, Qt::KeepAspectRatio));

	/* background 7 */
	ui->backgroundText_7->setAlignment(Qt::AlignCenter);
	ui->backgroundText_7->setWordWrap(true);
	ui->img_7->setMinimumSize(1, 1);
	ui->img_7->setPixmap(dude.scaled(w, h, Qt::KeepAspectRatio));
	/* game image */
	QPixmap dude2(":/images/ImagesLevel6/lean.png");
	int dw = ui->dudeImg->width();
	int dh = ui->dudeImg->height();
	ui->dudeImg->setMinimumSize(1, 1);
	ui->dudeImg->setPixmap(dude2.scaled(dw, dh, Qt::KeepAspectRatio)
				   .transformed(QTransform().scale(-1, 1)));
	//    ui->dudeImg->setMinimumSize(1,1);
	//    ui->dudeImg->setPixmap();
}

Level4::~Level4()
{
	for (Level4Square *s : this->squares)
	{
		delete s;
		s = nullptr;
	}
	delete this->ground;
	delete this->scene;
	delete this->world;
	delete ui;
}

void Level4::showWinMessage()
{
	winTheGame = true;
	ui->proceedButton->setEnabled(true);
	ui->message->setText(QString("Correct!"));
	ui->message->setStyleSheet(
	    QString("background-color: black; color: green;"));
	this->score += 100;
	ScoreContext::SetScore(3, this->score);
	ui->rightAnsButton->setEnabled(false);
	ui->wrongAnsButton->setEnabled(false);
	ui->proceedButton->setEnabled(true);
}

void Level4::showLoseMessage()
{
	ui->message->setText(QString("Wrong!"));
	ui->message->setStyleSheet(
	    QString("background-color: black; color: red;"));
	ui->rightAnsButton->setEnabled(false);
	ui->wrongAnsButton->setEnabled(false);
	ui->proceedButton->setEnabled(true);
}

void Level4::showTutorial()
{
	ui->stackedWidget->setCurrentIndex(10);
	ui->instructionLabel->setText("The area of the blue square is x * x");
}

void Level4::showPieShape()
{

	//	ui->showSurpriseLabel->setVisible(true);
	ui->surpriseLabel->setVisible(false);
	ui->endGameButton->setVisible(true);
	//	ui->seeThePieButton->setVisible(false);

	showPie = true;

	QWidget::update();
}

void Level4::showGameplay()
{
	ui->stackedWidget->setCurrentWidget(ui->gameUI);

	linearConst = random.bounded(4, 20);
	this->score = 0;

	while (linearConst % 2 != 0 || containsNum(linearConst))
	{
		linearConst = random.bounded(4, 20);
	}

	// linearConst = random.bounded(2,10);
	ui->message->setText("Choose The Right One!");
	ui->message->setStyleSheet(
	    QString("background-color: black; color: white;"));

	QString LinearStr = QString::number(linearConst);

	QString expression("x * x + ");
	expression.append(LinearStr);
	expression.append(" x ");
	expression.append(" + _____");

	// QString expression =
	// QString("x*x").append(linearConst).append("x").append("___");
	QString instruction =
	    QString("Complete the square for: ").append(expression);
	ui->completeSquareLabel->setText(instruction);
	updateGameButtons();
}

void Level4::showintroduction()
{

	if (ui->stackedWidget->currentIndex() != 1)
	{
		ui->stackedWidget->setCurrentIndex(1);
	}

	introductionStep++;

	switch (introductionStep)
	{
	case 1:
		ui->introduction->setVisible(true);
		ui->introduction->setStyleSheet(QString("color: gray"));

		ui->task->setVisible(false);
		ui->result1->setVisible(false);
		ui->result2->setVisible(false);
		ui->nextButton->setVisible(true);

		ui->response->setText(
		    "Math is too ivory tower, I dont't see it wiil work.");

		break;
	case 2:
		ui->introduction->setVisible(false);

		ui->task->setVisible(true);
		ui->task->setStyleSheet(
		    QString("background-color: black; color: white;"));

		ui->result1->setVisible(false);
		ui->result2->setVisible(false);
		ui->nextButton->setVisible(true);

		ui->response->setText(
		    "I don't need myself to solve Math problem!.");
		break;
	case 3:
		ui->introduction->setVisible(false);

		ui->task->setVisible(false);

		ui->result1->setVisible(true);
		ui->result2->setVisible(false);
		ui->result1->setStyleSheet(QString("color: yellow"));

		ui->response->setText(
		    "How does that letting me embrance Math?.");

		ui->nextButton->setVisible(true);
		break;
	case 4:
		ui->introduction->setVisible(false);
		ui->task->setVisible(false);
		ui->result1->setVisible(false);
		ui->result2->setVisible(true);
		ui->result2->setStyleSheet(QString("color: red"));

		ui->nextButton->setVisible(false);
		ui->goTotutorialButton->setVisible(true);

		ui->response->setText("Cool! Can't wait to see the pie.");
		break;
	}
}

void Level4::showprologue()
{
	ui->stackedWidget->setCurrentWidget(ui->prologue);
	ui->scoreLabel->setText(
	    QString::fromStdString(std::to_string(this->score)));
	ui->scoreLabel->setStyleSheet("background-color: black; color: white;");
	ui->endGameButton->setVisible(true);
}

bool Level4::containsNum(int num)
{

	for (int i = 0; i < sequences.size(); i++)
	{
		if (sequences.at(i) == num)
		{
			return true;
		}
	}

	return false;
}

void Level4::updateGameButtons()
{
	/* Maybe swap the buttons. */
	if (rand() % 2)
	{
		QPoint Right = this->ui->rightAnsButton->pos();
		QPoint Wrong = this->ui->wrongAnsButton->pos();
		/* Swap them. */
		this->ui->wrongAnsButton->move(Right);
		this->ui->rightAnsButton->move(Wrong);
	}
	int rightAns = linearConst * linearConst / 4;
	ui->rightAnsButton->setText(QString::number(rightAns));
	ui->rightAnsButton->setEnabled(true);
	ui->wrongAnsButton->setEnabled(true);
}

void Level4::endGame()
{
	ui->stackedWidget->setCurrentWidget(ui->end);
	ui->proceedButton->setEnabled(false);
	ui->message->setStyleSheet(
	    QString("background-color: black; color: white;"));
	ui->message->setText("Choose The Right One!");

	ui->nextStepButton->setVisible(true);
	ui->beginGameButton->setVisible(false);

	//	ui->showSurpriseLabel->setVisible(false);
	//	ui->seeThePieButton->setVisible(false);
	ui->endGameButton->setVisible(false);

	showPie = false;
}

void Level4::updateGame()
{
	round++;
	winTheGame = false;
	ui->proceedButton->setEnabled(false);

	if (round >= maxRound)
	{
		showprologue();
	}

	ui->message->setText("Choose The Right One!");
	ui->message->setStyleSheet(
	    QString("background-color: black; color: white;"));

	linearConst = random.bounded(4, 20);

	while (linearConst % 2 != 0 || containsNum(linearConst))
	{
		linearConst = random.bounded(4, 20);
	}

	QString LinearStr = QString::number(linearConst);

	QString expression("x * x + ");
	expression.append(LinearStr);
	expression.append(" x ");
	expression.append(" + _____");

	QString instruction =
	    QString("Complete the square for: ").append(expression);
	ui->completeSquareLabel->setText(instruction);

	updateGameButtons();
	// linearConst = random.bounded(5);
}

void Level4::returnToStartScreen()
{
	Level4::createWorld();
	ui->stackedWidget->setCurrentIndex(0);

	ui->nextButton->setVisible(false);
	ui->goTotutorialButton->setVisible(false);

	round = 0;
	tutorialStep = 0;
	introductionStep = 0;
	seed++;
}

void Level4::createWorld()
{
	for (int i = 0; i < this->squares.length(); i++)
	{
		if (this->squares.at(i) == nullptr)
		{
			Level4Square *s = new Level4Square(
			    this->world, 100 + (i * 120), 100.0f);
			this->squares.replace(i, s);
			connect(this, &Level4::moveSignal, s,
				&Level4Square::moveSlot);
			this->scene->addItem(s);
		}
		else
		{
			this->squares.at(i)->applyImpuse();
		}
	}
	ui->graphicsView->show();

	if (!this->startedWorldUpdates)
	{ /* Make sure we only have one timer going */
		QTimer::singleShot(30, this, &Level4::updateWorld);
		this->startedWorldUpdates = true;
	}
}

/* Updates bodies in Box2D world */
void Level4::updateWorld()
{
	if (this->startedWorldUpdates)
	{
		/* Box2d step to next position */
		if (this->world)
			this->world->Step(1.0 / 60.0, 8,
					  4); /* Fixed timestep and iterations
					     as per box2d documentation */

		emit moveSignal();
		QTimer::singleShot(30, this, &Level4::updateWorld);
	}
	else
		return;
}

void Level4::onLevel4Clicked()
{
	Level4::createWorld();
	ui->stackedWidget->setCurrentWidget(ui->startMenu);
}

void Level4::showinstructions()
{
	tutorialStep++;

	QWidget::update();

	switch (tutorialStep)
	{
	case 1:
		ui->instructionLabel->setText("The blue has an area of x*2");
		break;
	case 2:
		ui->instructionLabel->setText("The blue has an area of x*2");
		break;
	case 3:
		ui->instructionLabel->setText("The gray has an area of 1");
		break;
	}

	if (tutorialStep >= 3)
	{
		ui->beginGameButton->setVisible(true);
		ui->nextStepButton->setVisible(false);
	}
}

void Level4::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);

	int UIWidth = ui->stackedWidget->width();
	int UIHeight = ui->stackedWidget->height();

	int x = 3 * UIWidth / 10;
	int y = 3 * UIHeight / 10;

	int squareLength = 150;
	int sideLength = 50;

	// QRect smallerSquare(x,y,squareLength,squareLength);
	// QRect smallerRec(x+squareLength,y,sideLength,squareLength);
	// QRect smallerRec2(x,y+squareLength,squareLength,sideLength);
	// QRect Square2(x+squareLength,y+squareLength,sideLength,sideLength);

	QRect gameplayRect(x, y, 40, 40);
	QBrush XSquarebrush(Qt::blue);
	QBrush CXBrush(Qt::red);
	QBrush CSquareBrush(Qt::gray);

	QBrush PieBrush(Qt::yellow);

	int currentIndex = ui->stackedWidget->currentIndex();
	QString numStr = QString::number(linearConst);

	if (currentIndex == 9)
	{
		switch (tutorialStep)
		{
		case 0:
			painter.drawText(x + squareLength / 2, y - 10,
					 QString("x"));
			painter.drawText(x - 15, y + squareLength / 2,
					 QString("x"));
			painter.fillRect(QuadSquare, XSquarebrush);
			break;
		case 1:
			painter.drawText(x + squareLength / 2, y - 10,
					 QString("x"));
			painter.drawText(x - 15, y + squareLength / 2,
					 QString("x"));
			painter.drawText(x + squareLength + sideLength / 2,
					 y - 10, QString("1"));
			painter.fillRect(QuadSquare, XSquarebrush);
			painter.fillRect(UpperLinearRectangle, CXBrush);

			break;
		case 2:
			painter.drawText(x + squareLength / 2, y - 10,
					 QString("x"));
			painter.drawText(x - 15, y + squareLength / 2,
					 QString("x"));
			painter.drawText(x + squareLength + sideLength / 2,
					 y - 10, QString("1"));
			painter.drawText(x - 15,
					 y + squareLength + sideLength / 2,
					 QString("1"));
			painter.fillRect(QuadSquare, XSquarebrush);
			painter.fillRect(UpperLinearRectangle, CXBrush);
			painter.fillRect(LowerLinearRectangle, CXBrush);
			break;
		case 3:
			painter.drawText(x + squareLength / 2, y - 10,
					 QString("x"));
			painter.drawText(x - 15, y + squareLength / 2,
					 QString("x"));
			painter.drawText(x + squareLength + sideLength / 2,
					 y - 10, QString("1"));
			painter.drawText(x - 15,
					 y + squareLength + sideLength / 2,
					 QString("1"));
			painter.fillRect(QuadSquare, XSquarebrush);
			painter.fillRect(UpperLinearRectangle, CXBrush);
			painter.fillRect(LowerLinearRectangle, CXBrush);
			painter.fillRect(ConstSquare, CSquareBrush);
			break;
		case 4:
			break;
		}
	}
	else if (currentIndex == 10)
	{
		painter.drawText(x + squareLength / 2, y - 10, QString("x"));
		painter.drawText(x + squareLength + sideLength / 2, y - 10,
				 QString("?"));

		painter.drawText(x - 15, y + squareLength / 2, QString("x"));
		painter.drawText(x - 15, y + squareLength + sideLength / 2,
				 QString("?"));

		painter.fillRect(QuadSquare, XSquarebrush);
		painter.fillRect(UpperLinearRectangle, CXBrush);
		painter.fillRect(LowerLinearRectangle, CXBrush);
		painter.fillRect(ConstSquare, CSquareBrush);
	}
	//    else if (currentIndex == 12)
	//	{
	//		if (showPie)
	//		{
	//			painter.setBrush(PieBrush);
	//			painter.drawPie(100, 100, 100, 100, 0, 360 *
	// 16);
	//		}
	//	}
}

/* Start background */
void Level4::on_startButton_clicked()
{
	this->startedWorldUpdates = false;
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage);
}

/* from 1st background page to 2nd */
void Level4::on_nextBtn_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage2);
}

void Level4::on_nextBtn_2_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage3);
}

void Level4::on_nextBtn_3_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage4);
}

void Level4::on_nextBtn_4_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage5);
}

void Level4::on_nextBtn_5_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage6);
}

void Level4::on_nextBtn_6_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->backgroundPage7);
}

void Level4::on_returnToMenuButton_clicked() { emit returnToSelectClicked(); }
void Level4::on_pushButton_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_clicked()
{
	this->startedWorldUpdates = false;
	emit returnToSelectClicked();
}
void Level4::on_levelButton_2_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_3_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_4_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_5_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_6_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_7_clicked() { emit returnToSelectClicked(); }
void Level4::on_levelButton_8_clicked() { emit returnToSelectClicked(); }
void Level4::on_endGameButton_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->end);
}

/* The start game button after the initial tutorial */
void Level4::on_nextBtn_7_clicked()
{
	//    showinstructions();
	showGameplay();
}
