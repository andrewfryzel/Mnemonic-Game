#include "level1navigator.h"
#include "level1.h"
level1navigator::level1navigator(QWidget *parent)
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
}
