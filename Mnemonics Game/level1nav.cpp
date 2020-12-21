#include "level1nav.h"
#include <level1.h>
#include <level1nav.h>
Level1Nav::Level1Nav(QWidget *parent) : QWidget(parent), ui(new Ui::Level1Nav)
{

	this->ui->setupUi(this);
	this->ui->stackedWidget->insertWidget(1, &lev1);

	this->connect(&lev1, SIGNAL(goBackClicked()), this,
		      SLOT(returnToLevel1()));
}

Level1Nav::~Level1Nav() { delete this->ui; }
