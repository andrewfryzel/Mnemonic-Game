#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setFixedSize(QSize(1050, 600));
	/* Instantiate the other classes. */
	/*
	 * ui->stackedWidget->addWidget(&SelectLevel);
	 */

	setObjectName("MainMenu"); /*We do this so that only the background will
				      change, not all widgets*/

	/* In order to change the background, the 2 lines below should be used
	 * so that not all QWidgets inherit the background. To go back to a
	 * default background simply remove the url portion.
	 */
	widgetStyle =
	    "QWidget#MainMenu {border-image: url(:/Pictures/Mountains3.jpg);}";
	setStyleSheet(widgetStyle);

	ui->stackedWidget->insertWidget(1, &SelectLevel);

	/*Signals and Slots Connect */
	this->connect(&SelectLevel, SIGNAL(homeButtonClicked()), this,
		      SLOT(returnToHome()));
	this->connect(&SelectLevel, SIGNAL(levelButtonClicked()), this,
		      SLOT(returnToDefaultBackground()));
	this->connect(&SelectLevel, SIGNAL(levelSelectClicked()), this,
		      SLOT(on_startButton_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_startButton_clicked()
{
	widgetStyle =
	    "QWidget#MainMenu {border-image: url(:/Pictures/Mountains2.png);}";
	setStyleSheet(widgetStyle);
	ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::returnToHome()
{
	widgetStyle =
	    "QWidget#MainMenu {border-image: url(:/Pictures/Mountains3.jpg);}";
	setStyleSheet(widgetStyle);
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_homeButton_clicked()
{
	widgetStyle =
	    "QWidget#MainMenu {border-image: url(:/Pictures/Mountains3.jpg);}";
	setStyleSheet(widgetStyle);
	ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::returnToDefaultBackground()
{
	widgetStyle = "QWidget#MainMenu {border-image: "
		      "url(:/Pictures/blue_background.png)}";
	setStyleSheet(widgetStyle);
}
