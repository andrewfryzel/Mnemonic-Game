#include "level6.h"
#include "ui_level6.h"
#include <QPixmap>
#include <QTime>
#include <QTimer>
#include <QtGlobal>
#include <stdint.h>

#include "scorecontext.h"

/* HACK: Store the score here for now. */
static uint64_t Score = 0;

Level6::Level6(QWidget *parent) : QWidget(parent), ui(new Ui::Level6)
{

	ui->setupUi(this);
	ui->nextLevel_2->setVisible(false);
	ui->nextLevel->setVisible(false);
	ui->loseLabel->setVisible(false);
	ui->jupiterButton->setText("");
	ui->saturnButton->setText("");
	ui->uranusButton->setText("");
	ui->neptuneButton->setText("");
	ui->jupiterButton_2->setText("");
	ui->saturnButton_2->setText("");
	ui->uranusButton_2->setText("");
	ui->neptuneButton_2->setText("");

	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");

	ui->mercButton->setFlat(true);
	ui->mercButton->setAutoFillBackground(true);

	// TUTORIAL//
	// Mercury
	QPixmap mercuryPix(":/new/prefix1/ImagesLevel6/mercury.jpg");
	ui->mercury->setPixmap(mercuryPix);
	ui->mercury->setScaledContents(true);
	ui->mercury->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->mercury->setVisible(false);

	// Venus
	QPixmap venusPix(":/new/prefix1/ImagesLevel6/venus.jpeg");
	ui->venus->setPixmap(venusPix);
	ui->venus->setScaledContents(true);
	ui->venus->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->venus->setVisible(false);

	// Earth
	QPixmap earthPix(":/new/prefix1/ImagesLevel6/earthIcon.png");
	ui->earth->setPixmap(earthPix);
	ui->earth->setScaledContents(true);
	ui->earth->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->earth->setVisible(false);
	ui->earth->setStyleSheet("QLabel{ background-color: black;}");

	// Mars
	QPixmap marsPix(":/new/prefix1/ImagesLevel6/marsIcon.png");
	ui->mars->setPixmap(marsPix);
	ui->mars->setScaledContents(true);
	ui->mars->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->mars->setVisible(false);
	ui->mars->setStyleSheet("QLabel{ background-color: black;}");

	// Jupiter
	QPixmap jupiterPix(":/new/prefix1/ImagesLevel6/jupiterIcon.png");
	ui->jupiter->setPixmap(jupiterPix);
	ui->jupiter->setScaledContents(true);
	ui->jupiter->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->jupiter->setVisible(false);
	ui->jupiter->setStyleSheet("QLabel{ background-color: black;}");

	// Saturn
	QPixmap saturnPix(":/new/prefix1/ImagesLevel6/saturnIcon.png");
	ui->saturn->setPixmap(saturnPix);
	ui->saturn->setScaledContents(true);
	ui->saturn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->saturn->setVisible(false);
	ui->saturn->setStyleSheet("QLabel{ background-color: black;}");

	// Uranus
	QPixmap uranusPix(":/new/prefix1/ImagesLevel6/uranusIcon.png");
	ui->uranus->setPixmap(uranusPix);
	ui->uranus->setScaledContents(true);
	ui->uranus->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->uranus->setVisible(false);
	ui->uranus->setStyleSheet("QLabel{ background-color: black;}");

	// Neptune
	QPixmap neptunePix(":/new/prefix1/ImagesLevel6/neptuneIcon.png");
	ui->neptune->setPixmap(neptunePix);
	ui->neptune->setScaledContents(true);
	ui->neptune->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->neptune->setVisible(false);
	ui->neptune->setStyleSheet("QLabel{ background-color: black;}");

	// Pluto
	QPixmap plutoPix(":/new/prefix1/ImagesLevel6/stick.png");
	ui->pluto->setPixmap(venusPix);
	ui->pluto->setScaledContents(true);
	ui->pluto->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
	ui->pluto->setVisible(false);

	// LEVEL1//

	ui->mercButton->show();
	ui->mercButton->setSizePolicy(QSizePolicy::Ignored,
				      QSizePolicy::Ignored);
	ui->mercButton->setFlat(true);
	ui->mercButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/mercuryIcon.png)");

	QPixmap venusPic(":/new/prefix1/ImagesLevel6/venus.jpeg");
	ui->venButton->show();
	ui->venButton->setVisible(true);
	ui->venButton->setSizePolicy(QSizePolicy::Ignored,
				     QSizePolicy::Ignored);
	ui->venButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/venusIcon.png)");

	QPixmap earthPic(":/new/prefix1/ImagesLevel6/earth.jpg");

	ui->earthButton->show();
	ui->earthButton->setSizePolicy(QSizePolicy::Ignored,
				       QSizePolicy::Ignored);
	ui->earthButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/earthIcon.png)");

	// ui->stackedWidget->setCurrentIndex(1);

	ui->mnemonicButton->setVisible(false);
	ui->playGameButton->setVisible(false);

	QPixmap pix(":/new/prefix1/ImagesLevel6/lean.png");
	ui->imageLabel->setPixmap(pix);
	ui->imageLabel->show();
	ui->imageLabel->setScaledContents(true);
	ui->imageLabel->setSizePolicy(QSizePolicy::Ignored,
				      QSizePolicy::Ignored);
	ui->imageLabel->setStyleSheet(
	    "QLabel{ background-color: transparent;}");

	// Mars
	QPixmap marsPix2(":/new/prefix1/ImagesLevel6/marsIcon.png");
	ui->marsButton->setSizePolicy(QSizePolicy::Ignored,
				      QSizePolicy::Ignored);
	ui->marsButton->setVisible(true);
	ui->marsButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/marsIcon.png)");

	// Jupiter
	QPixmap jupiterPix2(":/new/prefix1/ImagesLevel6/jupiterIcon.png");
	ui->jupiterButton->setSizePolicy(QSizePolicy::Ignored,
					 QSizePolicy::Ignored);
	ui->jupiterButton->setVisible(true);
	ui->jupiterButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/jupiterIcon.png)");

	// Saturn
	QPixmap saturnPix2(":/new/prefix1/ImagesLevel6/saturnIcon.png");
	ui->saturnButton->setSizePolicy(QSizePolicy::Ignored,
					QSizePolicy::Ignored);
	ui->saturnButton->setVisible(true);
	ui->saturnButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/saturnIcon.png)");

	// Uranus
	QPixmap uranusPix2(":/new/prefix1/ImagesLevel6/uranusIcon.png");
	ui->uranusButton->setSizePolicy(QSizePolicy::Ignored,
					QSizePolicy::Ignored);
	ui->uranusButton->setVisible(true);
	ui->uranusButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/uranusIcon.png)");

	// Neptune
	QPixmap neptunePix2(":/new/prefix1/ImagesLevel6/neptuneIcon.png");
	ui->neptuneButton->setSizePolicy(QSizePolicy::Ignored,
					 QSizePolicy::Ignored);
	ui->neptuneButton->setVisible(true);
	ui->neptuneButton->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/neptuneIcon.png)");

	//-------------------2---------------//

	// Mercury
	ui->mercButton_2->show();
	ui->mercButton_2->setSizePolicy(QSizePolicy::Ignored,
					QSizePolicy::Ignored);
	ui->mercButton_2->setFlat(true);
	ui->mercButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/mercuryIcon.png)");

	ui->venButton_2->show();
	ui->venButton_2->setVisible(true);
	ui->venButton_2->setSizePolicy(QSizePolicy::Ignored,
				       QSizePolicy::Ignored);
	ui->venButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/venusIcon.png)");

	ui->earthButton_2->show();
	ui->earthButton_2->setSizePolicy(QSizePolicy::Ignored,
					 QSizePolicy::Ignored);
	ui->earthButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/earthIcon.png)");

	// Mars
	ui->marsButton_2->setSizePolicy(QSizePolicy::Ignored,
					QSizePolicy::Ignored);
	ui->marsButton_2->setVisible(true);
	ui->marsButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/marsIcon.png)");

	// Jupiter
	ui->jupiterButton_2->setSizePolicy(QSizePolicy::Ignored,
					   QSizePolicy::Ignored);
	ui->jupiterButton_2->setVisible(true);
	ui->jupiterButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/jupiterIcon.png)");

	// Saturn
	ui->saturnButton_2->setSizePolicy(QSizePolicy::Ignored,
					  QSizePolicy::Ignored);
	ui->saturnButton_2->setVisible(true);
	ui->saturnButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/saturnIcon.png)");

	// Uranus
	ui->uranusButton_2->setSizePolicy(QSizePolicy::Ignored,
					  QSizePolicy::Ignored);
	ui->uranusButton_2->setVisible(true);
	ui->uranusButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/uranusIcon.png)");

	// Neptune
	ui->neptuneButton_2->setSizePolicy(QSizePolicy::Ignored,
					   QSizePolicy::Ignored);
	ui->neptuneButton_2->setVisible(true);
	ui->neptuneButton_2->setStyleSheet(
	    "border-image: url(:/new/prefix1/ImagesLevel6/neptuneIcon.png)");

	ui->chatLabel1->setStyleSheet("border: 2px solid black");
	ui->chatLabel1->setText("What kind of music do planets sing?");
	ui->contStart->setVisible(false);
	ui->contStart->setEnabled(false);

	ui->terresBorder->setStyleSheet("border: 4px solid blue");
	ui->terresBorder->setVisible(false);

	ui->gasBorder->setStyleSheet("border: 4px solid red");
	ui->gasBorder->setVisible(false);

	ui->mercLabel->setStyleSheet("border: 2px solid black");
	ui->mercLabel->setVisible(false);

	ui->venusLabel->setStyleSheet("border: 2px solid black");
	ui->venusLabel->setVisible(false);

	ui->earthLabel->setStyleSheet("border: 2px solid black");
	ui->earthLabel->setVisible(false);

	ui->marsLabel->setStyleSheet("border: 2px solid black");
	ui->marsLabel->setVisible(false);

	ui->jupLabel->setStyleSheet("border: 2px solid black");
	ui->jupLabel->setVisible(false);

	ui->satLabel->setStyleSheet("border: 2px solid black");
	ui->satLabel->setVisible(false);

	ui->uranLabel->setStyleSheet("border: 2px solid black");
	ui->uranLabel->setVisible(false);

	ui->neptLabel->setStyleSheet("border: 2px solid black");
	ui->neptLabel->setVisible(false);

	// QTimer::singleShot(1000, this, SLOT(startText()));

	ui->pushButton->setVisible(false);
	ui->pushButton_2->setVisible(false);
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
}

Level6::~Level6() { delete ui; }

void Level6::delay(int amount)
{
	QTime delay = QTime::currentTime().addMSecs(amount);
	while (QTime::currentTime() < delay)
	{
		QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
	}
}

void Level6::startText() { ui->startevel6->setText(""); }

void Level6::on_startevel6_clicked()
{

	ui->chatLabel1->setText("Nep-tunes!");
	QPixmap pix(":/new/prefix1/ImagesLevel6/point.png");
	ui->imageLabel->setPixmap(pix);
	ui->startevel6->setVisible((false));
	ui->startevel6->setEnabled(false);

	delay(1000);

	ui->contStart->setText("");

	ui->contStart->setVisible(true);
	ui->contStart->setEnabled(true);
}

void Level6::on_contStart_clicked()
{
	ui->chatLabel1->setText(
	    "This level is all about space! Do you like space? ");
	QPixmap pix(":/new/prefix1/ImagesLevel6/stick.png");
	ui->imageLabel->setPixmap(pix);
	this->setStyleSheet(
	    "#page { "
	    " background-image: url(:/new/prefix1/ImagesLevel6/space.jpg)"
	    "}");

	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");

	ui->label_10->setStyleSheet("border: 0px solid white");
	ui->label_8->setStyleSheet("border: 0px solid white");
	ui->label_9->setStyleSheet("border: 0px solid white");
	ui->label_3->setStyleSheet("border: 0px solid white");
	ui->label_7->setStyleSheet("border: 0px solid white");
	ui->label_6->setStyleSheet("border: 0px solid white");
	ui->label_5->setStyleSheet("border: 0px solid white");
	ui->label_4->setStyleSheet("border: 0px solid white");

	ui->label_10->setStyleSheet("border: 0px solid yellow");
	ui->label_8->setStyleSheet("border: 0px solid yellow");
	ui->label_9->setStyleSheet("border: 0px solid yellow");
	ui->label_3->setStyleSheet("border: 0px solid yellow");
	ui->label_7->setStyleSheet("border: 0px solid yellow");
	ui->label_6->setStyleSheet("border: 0px solid yellow");
	ui->label_5->setStyleSheet("border: 0px solid yellow");
	ui->label_4->setStyleSheet("border: 0px solid yellow");

	ui->gasBorder->setStyleSheet("QLabel{ background-color: white;}");
	ui->terresBorder->setStyleSheet("QLabel{ background-color: white;}");

	// qApp->setStyleSheet("QLabel{ background-color: white }");

	ui->startevel6->setVisible(false);
	ui->startevel6->setEnabled(false);
	ui->contStart->setVisible(false);
	ui->contStart->setEnabled(false);

	delay(2000);

	ui->pushButton->setVisible(true);
	ui->pushButton_2->setVisible(true);
	ui->pushButton->setEnabled(true);
	ui->pushButton_2->setEnabled(true);
}

void Level6::on_pushButton_clicked()
{
	ui->chatLabel1->setText("It is pretty OUT OF THIS WORLD!");
	ui->pushButton->setVisible(false);
	ui->pushButton_2->setVisible(false);
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);

	startTutorial();
}

void Level6::on_pushButton_2_clicked()
{
	ui->pushButton->setVisible(false);
	ui->pushButton_2->setVisible(false);
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
	ui->chatLabel1->setText("Lets try that again!");
	// thumbs down

	delay(2000);

	ui->chatLabel1->setText("Do you like space?");

	delay(500);
	ui->pushButton->setVisible(true);
	ui->pushButton_2->setVisible(true);
	ui->pushButton->setEnabled(true);
	ui->pushButton_2->setEnabled(true);

	QPixmap pix(":/new/prefix1/ImagesLevel6/stick.png");
	ui->imageLabel->setPixmap(pix);

	ui->startevel6->setVisible(false);
	ui->startevel6->setEnabled(false);
	ui->contStart->setVisible(false);
	ui->contStart->setEnabled(false);

	delay(2000);

	ui->pushButton->setVisible(true);
	ui->pushButton_2->setVisible(true);
	ui->pushButton->setEnabled(true);
	ui->pushButton_2->setEnabled(true);

	ui->pushButton->setVisible(false);
	ui->pushButton_2->setVisible(false);
	ui->pushButton->setEnabled(false);
	ui->pushButton_2->setEnabled(false);
}

void Level6::generateJoke()
{
	if (count == 0)
	{

		count++;
	}

	else if (count == 1)
	{

		count++;
	}
	else if (count == 2)
	{

		count++;
	}
	else if (count == 3)
	{

		count++;
	}

	else if (count == 6)
	{

		count++;
	}
}

void Level6::startTutorial()
{
	ui->chatLabel1->setText(
	    "Within out solar system, there are 9 planets!");

	showPlanets();
	// ui->chatLabel1->setText("Some say that Pluto isn't a planet, however,
	// theyre wrong!");
}

void Level6::showPlanets()
{
	ui->chatLabel1->setText(
	    "The planets can be seperated into two categories: ");

	delay(2000);

	ui->chatLabel1->setText("Rocky Planets: ");
	delay(1000);

	ui->mercury->setVisible(true);
	ui->mercLabel->setVisible(true);
	delay(1000);

	ui->venus->setVisible(true);
	ui->venusLabel->setVisible(true);
	delay(1000);

	ui->earth->setVisible(true);
	ui->earthLabel->setVisible(true);
	delay(1000);

	ui->mars->setVisible(true);
	ui->marsLabel->setVisible(true);
	delay(1000);
	ui->terresBorder->setVisible(true);

	delay(1000);
	ui->chatLabel1->setText("And Gas Planets: ");

	delay(1000);

	ui->jupiter->setVisible(true);
	ui->jupLabel->setVisible(true);
	delay(1000);

	ui->saturn->setVisible(true);
	ui->satLabel->setVisible(true);
	delay(1000);

	ui->uranus->setVisible(true);
	ui->uranLabel->setVisible(true);
	delay(1000);

	ui->neptune->setVisible(true);
	ui->neptLabel->setVisible(true);
	delay(1000);

	ui->gasBorder->setVisible(true);

	// ui->pluto->setVisible(true);

	// TODO
	// COLOR PLANET BORDERS
	delay(1000);
	ui->mnemonicButton->setEnabled(true);
	ui->mnemonicButton->setVisible(true);
}

void Level6::on_mnemonicButton_clicked()
{
	ui->mnemonicButton->setVisible(false);
	ui->mnemonicButton->setEnabled(false);

	ui->chatLabel1->setText(
	    "Lets learn how to remember the order of the planets!");
	delay(1000);

	ui->chatLabel1->setText("Use this phrase!");
	delay(1500);

	ui->mercLabel->setText("My");
	ui->chatLabel1->setText("My");
	flashLabel(ui->mercLabel, ui->mercury);
	ui->mercury->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->venusLabel->setText("Very");
	ui->chatLabel1->setText("My Very");
	flashLabel(ui->venusLabel, ui->venus);
	ui->venus->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->earthLabel->setText("Excited");
	ui->chatLabel1->setText("My Very Excited");
	flashLabel(ui->earthLabel, ui->earth);
	ui->earth->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->marsLabel->setText("Mother");
	ui->chatLabel1->setText("My Very Excited Mother");
	flashLabel(ui->marsLabel, ui->mars);
	ui->mars->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->jupLabel->setText("Just");
	ui->chatLabel1->setText("My Very Excited Mother Just");
	flashLabel(ui->jupLabel, ui->jupiter);
	ui->jupiter->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->satLabel->setText("Served");
	ui->chatLabel1->setText("My Very Excited Mother Just Served");
	flashLabel(ui->satLabel, ui->saturn);
	ui->saturn->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->uranLabel->setText("Us");
	ui->chatLabel1->setText("My Very Excited Mother Just Served Us");
	flashLabel(ui->uranLabel, ui->uranus);
	ui->uranus->setStyleSheet("QLabel{ background-color: black;}");

	delay(500);

	ui->neptLabel->setText("Nachos");
	ui->chatLabel1->setText("My Very Excited Mother Just Served Us Nachos");
	flashLabel(ui->neptLabel, ui->neptune);
	ui->neptune->setStyleSheet("QLabel{ background-color: black;}");

	ui->chatLabel1->setText(
	    "Remember that: My Very Excited Mother Just Served Us Nachos\nand "
	    "you'll always remember the order of the planets!");
	delay(500);
	ui->playGameButton->setVisible(true);
}

void Level6::flashLabel(QLabel *label, QLabel *label2)
{
	label2->setStyleSheet("QLabel{ background-color: black;}");

	label->setStyleSheet("border: 4px solid yellow");
	label2->setStyleSheet("border: 4px solid yellow");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
	delay(200);

	label->setStyleSheet("border: 4px solid white");
	label2->setStyleSheet("border: 4px solid white");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
	delay(200);

	label->setStyleSheet("border: 4px solid yellow");
	label2->setStyleSheet("border: 4px solid yellow");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
	delay(200);

	label->setStyleSheet("border: 4px solid white");
	label2->setStyleSheet("border: 4px solid white");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
	delay(200);

	label->setStyleSheet("border: 2px solid yellow");
	label2->setStyleSheet("border: 2px solid yellow");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
	delay(200);

	label2->setStyleSheet("QLabel{ background-color: black;}");
	ui->chatLabel1->setStyleSheet("QLabel{ background-color: white;}");
	ui->mercLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->venusLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->earthLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->marsLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->jupLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->satLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->uranLabel->setStyleSheet("QLabel{ background-color: white;}");
	ui->neptLabel->setStyleSheet("QLabel{ background-color: white;}");
}

void Level6::on_playGameButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}

void Level6::on_checkButton_clicked() {}

void Level6::on_levelButton_2_clicked()
{
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);
	ui->label_10->setStyleSheet("border: 0px solid white");
	ui->label_8->setStyleSheet("border: 0px solid white");
	ui->label_9->setStyleSheet("border: 0px solid white");
	ui->label_3->setStyleSheet("border: 0px solid white");
	ui->label_7->setStyleSheet("border: 0px solid white");
	ui->label_6->setStyleSheet("border: 0px solid white");
	ui->label_5->setStyleSheet("border: 0px solid white");
	ui->label_4->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->nextLevel->setVisible(false);

	emit returnToSelectClicked();
	ui->stackedWidget->setCurrentIndex(1);
}

void Level6::on_levelButton_clicked()
{
	emit returnToSelectClicked();
	ui->stackedWidget->setCurrentWidget(ui->page);
}

void Level6::on_mercButton_clicked()
{
	ui->mercButton->setEnabled(false);
	ui->label_3->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 0)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_venButton_clicked()
{
	ui->venButton->setEnabled(false);
	ui->label_4->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 1)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_earthButton_clicked()
{
	ui->earthButton->setEnabled(false);
	ui->label_5->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 2)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_marsButton_clicked()
{
	ui->marsButton->setEnabled(false);
	ui->label_6->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 3)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_jupiterButton_clicked()
{
	ui->jupiterButton->setEnabled(false);
	ui->label_7->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 4)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}
void Level6::on_saturnButton_clicked()
{
	ui->saturnButton->setEnabled(false);
	ui->label_8->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 5)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_uranusButton_clicked()
{
	ui->uranusButton->setEnabled(false);
	ui->label_9->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 6)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_neptuneButton_clicked()
{
	ui->neptuneButton->setEnabled(false);
	ui->label_10->setStyleSheet("border: 3px solid yellow");

	track++;
	if (count == 7)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel->setVisible(true);
			ui->loseLabel->setText("LOSE");
		}
		else if (count == 8)
		{
			ui->loseLabel->setText("WIN");
			ui->loseLabel->setVisible(true);
			ui->nextLevel_2->setVisible(true);
			ui->nextLevel->setVisible(true);
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_nextLevel_2_clicked() { ui->stackedWidget->setCurrentIndex(2); }

void Level6::on_nextLevel_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
	// ui->saturn_2->setStyleSheet("QLabel{ background-color: rgb(255, 1,
	// 255)}");

	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->mercuryIcon_2->setStyleSheet("border: 0px solid white");
	ui->venusIcon_2->setStyleSheet("border: 0px solid white");
	ui->earthIcon_2->setStyleSheet("border: 0px solid white");
	ui->marsIcon_2->setStyleSheet("border: 0px solid white");
	ui->jupiter_3->setStyleSheet("border: 0px solid white");
	ui->saturn_3->setStyleSheet("border: 0px solid white");
	ui->uranus_3->setStyleSheet("border: 0px solid white");
	ui->neptune_3->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);
	ui->nextLevel->setVisible(false);
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);
	ui->label_10->setStyleSheet("border: 0px solid white");
	ui->label_8->setStyleSheet("border: 0px solid white");
	ui->label_9->setStyleSheet("border: 0px solid white");
	ui->label_3->setStyleSheet("border: 0px solid white");
	ui->label_7->setStyleSheet("border: 0px solid white");
	ui->label_6->setStyleSheet("border: 0px solid white");
	ui->label_5->setStyleSheet("border: 0px solid white");
	ui->label_4->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->nextLevel->setVisible(false);
	ui->loseLabel_2->setVisible(false);
	ui->nextLevel_2->setVisible(false);
	count = 0;
	track = 0;
}

/*-----------------------------------------------------------*/

void Level6::on_venButton_2_clicked()
{
	ui->venButton_2->setEnabled(false);
	ui->venusIcon_2->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 1)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_earthButton_2_clicked()
{
	ui->earthButton_2->setEnabled(false);
	ui->earthIcon_2->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 2)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_mercButton_2_clicked()
{
	ui->mercButton_2->setEnabled(false);
	ui->mercuryIcon_2->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 0)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_marsButton_2_clicked()
{
	ui->marsButton_2->setEnabled(false);
	ui->marsIcon_2->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 3)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_jupiterButton_2_clicked()
{
	ui->jupiterButton_2->setEnabled(false);
	ui->jupiter_3->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 4)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}
void Level6::on_saturnButton_2_clicked()
{
	ui->saturnButton_2->setEnabled(false);
	ui->saturn_3->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 5)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_uranusButton_2_clicked()
{
	ui->uranusButton_2->setEnabled(false);
	ui->uranus_3->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 6)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else
		{
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_neptuneButton_2_clicked()
{
	ui->neptuneButton_2->setEnabled(false);
	ui->neptune_3->setStyleSheet("border: 3px solid yellow");
	track++;
	if (count == 7)
	{
		count++;
	}
	else
	{
		count--;
	}
	if (track == 8)
	{
		if (count != 8)
		{
			ui->loseLabel_2->setVisible(true);
			ui->loseLabel_2->setText("LOSE");
		}
		else if (count == 8)
		{
			ui->loseLabel_2->setText("WIN");

			ui->loseLabel_2->setVisible(true);
			ui->nextLevel_2->setVisible(true);
			ui->nextLevel->setVisible(true);
			Score += 50;
			ScoreContext::SetScore(5, Score);
		}
	}
}

void Level6::on_restartButton_clicked()
{
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);
	ui->label_10->setStyleSheet("border: 0px solid white");
	ui->label_8->setStyleSheet("border: 0px solid white");
	ui->label_9->setStyleSheet("border: 0px solid white");
	ui->label_3->setStyleSheet("border: 0px solid white");
	ui->label_7->setStyleSheet("border: 0px solid white");
	ui->label_6->setStyleSheet("border: 0px solid white");
	ui->label_5->setStyleSheet("border: 0px solid white");
	ui->label_4->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->nextLevel->setVisible(false);
}

void Level6::on_restartButton_2_clicked()
{
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->mercuryIcon_2->setStyleSheet("border: 0px solid white");
	ui->venusIcon_2->setStyleSheet("border: 0px solid white");
	ui->earthIcon_2->setStyleSheet("border: 0px solid white");
	ui->marsIcon_2->setStyleSheet("border: 0px solid white");
	ui->jupiter_3->setStyleSheet("border: 0px solid white");
	ui->saturn_3->setStyleSheet("border: 0px solid white");
	ui->uranus_3->setStyleSheet("border: 0px solid white");
	ui->neptune_3->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);
	ui->nextLevel->setVisible(false);
}

void Level6::on_selectLevelButton_2_clicked()
{
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->mercuryIcon_2->setStyleSheet("border: 0px solid white");
	ui->venusIcon_2->setStyleSheet("border: 0px solid white");
	ui->earthIcon_2->setStyleSheet("border: 0px solid white");
	ui->marsIcon_2->setStyleSheet("border: 0px solid white");
	ui->jupiter_3->setStyleSheet("border: 0px solid white");
	ui->saturn_3->setStyleSheet("border: 0px solid white");
	ui->uranus_3->setStyleSheet("border: 0px solid white");
	ui->neptune_3->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);
	ui->nextLevel->setVisible(false);
	count = 0;
	track = 0;
	ui->loseLabel->setVisible(false);
	ui->label_10->setStyleSheet("border: 0px solid white");
	ui->label_8->setStyleSheet("border: 0px solid white");
	ui->label_9->setStyleSheet("border: 0px solid white");
	ui->label_3->setStyleSheet("border: 0px solid white");
	ui->label_7->setStyleSheet("border: 0px solid white");
	ui->label_6->setStyleSheet("border: 0px solid white");
	ui->label_5->setStyleSheet("border: 0px solid white");
	ui->label_4->setStyleSheet("border: 0px solid white");

	ui->venButton->setEnabled(true);
	ui->mercButton->setEnabled(true);
	ui->earthButton->setEnabled(true);
	ui->marsButton->setEnabled(true);
	ui->jupiterButton->setEnabled(true);
	ui->saturnButton->setEnabled(true);
	ui->uranusButton->setEnabled(true);
	ui->neptuneButton->setEnabled(true);

	ui->loseLabel->setVisible(false);
	ui->nextLevel_2->setVisible(false);

	ui->nextLevel->setVisible(false);

	ui->loseLabel_2->setVisible(false);
	ui->venButton_2->setEnabled(true);
	ui->mercButton_2->setEnabled(true);
	ui->earthButton_2->setEnabled(true);
	ui->marsButton_2->setEnabled(true);
	ui->jupiterButton_2->setEnabled(true);
	ui->saturnButton_2->setEnabled(true);
	ui->uranusButton_2->setEnabled(true);
	ui->neptuneButton_2->setEnabled(true);

	ui->nextLevel->setVisible(false);
	emit returnToSelectClicked();
	ui->stackedWidget->setCurrentIndex(1);
}

void Level6::on_levelButton_3_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
}
