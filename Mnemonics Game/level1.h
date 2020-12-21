#ifndef LEVEL1_H
#define LEVEL1_H

#include <QWidget>

namespace Ui
{
	class Level1;
}

class Level1 : public QWidget
{
	Q_OBJECT

      public:
	explicit Level1(QWidget *parent = nullptr);
	~Level1();

      private slots:
	void on_levelButton_clicked();
	void on_rhymeButton_clicked();
	void on_verbalgimmickButton_clicked();
	void on_poemButton_clicked();
	void on_associationButton_clicked();
	void on_acronymButton_clicked();
	void on_crosswordsButton_clicked();
	void on_numbersgameButton_clicked();
	void on_makingaspeechButton_clicked();
	void returnToNav();
	void on_goBack_clicked();
	void on_goBack_2_clicked();
	void on_goBack_3_clicked();
	void on_goBack_4_clicked();
	void on_goBack_5_clicked();
	void on_goBack_6_clicked();
	void on_goBack_7_clicked();
	void on_goBack_8_clicked();

      signals:
	void returnToSelectClicked();
	void goBackClicked();

      private:
	Ui::Level1 *ui;
};

#endif // LEVEL1_H
