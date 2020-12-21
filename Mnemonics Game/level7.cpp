#include "level7.h"
#include "ui_level7.h"
#include <QKeyEvent>
#include <QTime>

#include "scorecontext.h"

Level7::Level7(QWidget *parent) : QWidget(parent), ui(new Ui::Level7)
{
	ui->setupUi(this);
	this->connect(this->ui->stackedWidget, &QStackedWidget::currentChanged,
		      this, [this]() { this->UpdateScores(); });
	this->ui->stackedWidget->setCurrentIndex(1);
	flag = 0;
}

Level7::~Level7() { delete ui; }

void Level7::UpdateScores()
{
	QString BaseText = QString("Level %1: %2");
	for (uint8_t Index = 1; Index < (5 + 1); ++Index)
	{
		QString Completed =
		    BaseText.arg(Index).arg(ScoreContext::GetScore(Index));

		if (Index == 1)
		{
			this->ui->Level1->setText(Completed);
		}
		else if (Index == 2)
		{
			this->ui->Level2->setText(Completed);
		}
		else if (Index == 3)
		{
			this->ui->Level3->setText(Completed);
		}
		else if (Index == 4)
		{
			this->ui->Level4->setText(Completed);
		}
		else if (Index == 5)
		{
			this->ui->Level5->setText(Completed);
		}
	}
	this->ui->lcdNumber->display(
	    static_cast<int>(ScoreContext::GetTotalScore()));
}

void Level7::keyPressEvent(QKeyEvent *event) {}

void Level7::startGame() {}

void Level7::delay(int amount)
{
	QTime delay = QTime::currentTime().addMSecs(amount);
	while (QTime::currentTime() < delay)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

void Level7::checkContact() {}

void Level7::on_levelButton_2_clicked() { emit returnToSelectClicked(); }

void Level7::on_levelButton_clicked()
{
	emit returnToSelectClicked();
	// ui->stackedWidget->setCurrentWidget(ui->page);
}

void Level7::on_pushButton_clicked()
{
	startGame();
	checkContact();
}
