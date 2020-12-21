#include "level1.h"
#include "ui_level1.h"
#include <QImage>
#include <QMessageBox>
#include <QPixmap>
#include <iostream>
Level1::Level1(QWidget *parent) : QWidget(parent), ui(new Ui::Level1)
{
	ui->setupUi(this);
	this->connect(this, SIGNAL(goBackClicked()), this, SLOT(returnToNav()));

	/* Label alignment and wrapping */
	ui->descriptionLabel->setWordWrap(true);
	ui->descriptionLabel->setAlignment(Qt::AlignCenter);
	ui->label->setWordWrap(true);
	ui->label->setAlignment(Qt::AlignCenter);
	ui->label_3->setWordWrap(true);
	ui->label_3->setAlignment(Qt::AlignCenter);
	ui->label_4->setWordWrap(true);
	ui->label_4->setAlignment(Qt::AlignCenter);
	ui->label_5->setWordWrap(true);
	ui->label_5->setAlignment(Qt::AlignCenter);
	ui->label_6->setWordWrap(true);
	ui->label_6->setAlignment(Qt::AlignCenter);
	ui->label_7->setWordWrap(true);
	ui->label_7->setAlignment(Qt::AlignCenter);
	ui->label_8->setWordWrap(true);
	ui->label_8->setAlignment(Qt::AlignCenter);
	ui->label_9->setWordWrap(true);
	ui->label_9->setAlignment(Qt::AlignCenter);

	/* teacher dude */
	QPixmap teacherImg(":/images/ImagesLevel6/lean.png");
	int w = ui->teacher->width();
	int h = ui->teacher->height();
	ui->teacher->setMinimumSize(1, 1);
	ui->teacher->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_2->setMinimumSize(1, 1);
	ui->teacher_2->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_3->setMinimumSize(1, 1);
	ui->teacher_3->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_4->setMinimumSize(1, 1);
	ui->teacher_4->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_5->setMinimumSize(1, 1);
	ui->teacher_5->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_6->setMinimumSize(1, 1);
	ui->teacher_6->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_7->setMinimumSize(1, 1);
	ui->teacher_7->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
	ui->teacher_8->setMinimumSize(1, 1);
	ui->teacher_8->setPixmap(teacherImg.scaled(w, h, Qt::KeepAspectRatio));
}

Level1::~Level1() { delete ui; }

void Level1::on_levelButton_clicked()
{
	emit returnToSelectClicked();
	ui->stackedWidget->setCurrentWidget(ui->navigationPage);
}

void Level1::on_rhymeButton_clicked() { ui->stackedWidget->setCurrentIndex(1); }

void Level1::on_verbalgimmickButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);
}

void Level1::on_poemButton_clicked() { ui->stackedWidget->setCurrentIndex(3); }

void Level1::on_associationButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(4);
}

void Level1::on_acronymButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(5);
}

void Level1::on_crosswordsButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(6);
}

void Level1::on_numbersgameButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(7);
}

void Level1::on_makingaspeechButton_clicked()
{
	ui->stackedWidget->setCurrentIndex(8);
}

void Level1::on_goBack_clicked() { emit goBackClicked(); }

void Level1::on_goBack_2_clicked() { emit goBackClicked(); }

void Level1::on_goBack_3_clicked() { emit goBackClicked(); }

void Level1::on_goBack_4_clicked() { emit goBackClicked(); }

void Level1::on_goBack_5_clicked() { emit goBackClicked(); }

void Level1::on_goBack_6_clicked() { emit goBackClicked(); }

void Level1::on_goBack_7_clicked() { emit goBackClicked(); }

void Level1::on_goBack_8_clicked() { emit goBackClicked(); }
void Level1::returnToNav() { ui->stackedWidget->setCurrentIndex(0); }
