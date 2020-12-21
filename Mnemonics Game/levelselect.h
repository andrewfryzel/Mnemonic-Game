#ifndef LEVELSELECT_H
#define LEVELSELECT_H

#include <QWidget>
#include <level1.h>
#include <level2.h>
#include <level3.h>
#include <level4.h>
#include <level5.h>
#include <level6.h>
#include <level7.h>

namespace Ui
{
	class LevelSelect;
}

class LevelSelect : public QWidget
{
	Q_OBJECT

      public:
	explicit LevelSelect(QWidget *parent = nullptr);
	~LevelSelect();

      private:
	Ui::LevelSelect *ui;
	Level1 lev1;
	Level2 lev2;
	Level3 lev3;
	Level4 lev4;
	Level5 lev5;
	Level6 lev6;
	Level7 lev7;

      signals:
	void homeButtonClicked();
	void levelSelectClicked();
	void levelButtonClicked();
	void level3Clicked();
	void level4Clicked();

      private slots:

	void on_homeButton_clicked();
	void on_level1Button_clicked();
	void returnToLevelSelect();
	void on_level2Button_clicked();
	void on_level3Button_clicked();
	void on_level4Button_clicked();
	void on_level5Button_clicked();
	void on_level6Button_clicked();
	void on_level7Button_clicked();
};

#endif // LEVELSELECT_H
