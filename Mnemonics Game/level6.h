#ifndef LEVEL6_H
#define LEVEL6_H

#include <QGraphicsItem>
#include <QLabel>
#include <QWidget>

namespace Ui
{
	class Level6;
}

class Level6 : public QWidget
{
	Q_OBJECT

      public:
	explicit Level6(QWidget *parent = nullptr);
	~Level6();
	int count = 0;
	int track = 0;

      private:
	Ui::Level6 *ui;
	void delay(int amount);
	void generateJoke();
	void startTutorial();
	void showPlanets();
	void flashLabel(QLabel *label, QLabel *label2);

      signals:
	void returnToSelectClicked();

      public slots:
	void on_pushButton_clicked();
	void startText();

      private slots:
	void on_startevel6_clicked();
	void on_contStart_clicked();
	void on_pushButton_2_clicked();
	void on_mnemonicButton_clicked();
	void on_playGameButton_clicked();
	void on_checkButton_clicked();
	void on_levelButton_2_clicked();
	void on_levelButton_clicked();

	void on_mercButton_clicked();
	void on_venButton_clicked();
	void on_earthButton_clicked();
	void on_marsButton_clicked();
	void on_nextLevel_2_clicked();
	void on_nextLevel_clicked();
	void on_venButton_2_clicked();
	void on_earthButton_2_clicked();
	void on_mercButton_2_clicked();
	void on_marsButton_2_clicked();
	void on_restartButton_clicked();
	void on_restartButton_2_clicked();
	void on_selectLevelButton_2_clicked();
	void on_jupiterButton_clicked();
	void on_saturnButton_clicked();
	void on_uranusButton_clicked();
	void on_neptuneButton_clicked();
	void on_saturnButton_2_clicked();
	void on_uranusButton_2_clicked();
	void on_jupiterButton_2_clicked();
	void on_neptuneButton_2_clicked();
	void on_levelButton_3_clicked();
};

#endif // LEVEL6_H
