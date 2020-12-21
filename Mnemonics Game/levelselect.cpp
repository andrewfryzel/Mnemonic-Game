#include "levelselect.h"
#include "mainwindow.h"
#include "ui_levelselect.h"
#include <level1.h>
#include <level2.h>
#include <level3.h>
#include <level4.h>
#include <level5.h>
#include <level6.h>
#include <level7.h>

LevelSelect::LevelSelect(QWidget *parent)
    : QWidget(parent), ui(new Ui::LevelSelect)
{
	this->ui->setupUi(this);
	this->ui->stackedWidget->insertWidget(1, &lev1);
	this->ui->stackedWidget->insertWidget(2, &lev2);
	this->ui->stackedWidget->insertWidget(3, &lev3);
	this->ui->stackedWidget->insertWidget(4, &lev4);
	this->ui->stackedWidget->insertWidget(5, &lev5);
	this->ui->stackedWidget->insertWidget(6, &lev6);
	this->ui->stackedWidget->insertWidget(7, &lev7);

	this->connect(&lev1, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev2, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev3, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev4, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev5, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev6, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(&lev7, SIGNAL(returnToSelectClicked()), this,
		      SLOT(returnToLevelSelect()));
	this->connect(this, SIGNAL(level3Clicked()), &lev3,
		      SLOT(onLevel3Clicked()));
	this->connect(this, SIGNAL(level4Clicked()), &lev4,
		      SLOT(onLevel4Clicked()));
}

LevelSelect::~LevelSelect() { delete this->ui; }

void LevelSelect::on_homeButton_clicked() { emit this->homeButtonClicked(); }

void LevelSelect::returnToLevelSelect()
{
	/* changes background back to level select background */
	emit this->levelSelectClicked();
	this->ui->stackedWidget->setCurrentIndex(0);
}

void LevelSelect::on_level1Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(1);
}

void LevelSelect::on_level2Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(2);
}

void LevelSelect::on_level3Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(3);
	emit level3Clicked();
}

void LevelSelect::on_level4Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(4);
	emit level4Clicked();
}

void LevelSelect::on_level5Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(5);
}

void LevelSelect::on_level6Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(6);
}

void LevelSelect::on_level7Button_clicked()
{
	emit this->levelButtonClicked();
	this->ui->stackedWidget->setCurrentIndex(7);

	this->lev7.UpdateScores();
}
