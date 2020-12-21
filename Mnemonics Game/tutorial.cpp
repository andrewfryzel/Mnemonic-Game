#include "tutorial.h"
#include "ui_tutorial.h"

Tutorial::Tutorial(QWidget *parent) : QWidget(parent), ui(new Ui::Tutorial)
{
	ui->setupUi(this);
}

Tutorial::~Tutorial() { delete ui; }

void Tutorial::on_levelSelectButton_clicked() { emit returnToSelectClicked(); }

void Tutorial::on_levelSelectButton2_clicked()
{
	emit returnToSelectClicked();
	// ui->stackedWidget->setCurrentWidget(ui->page);
}
