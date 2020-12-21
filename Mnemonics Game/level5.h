#ifndef LEVEL5_H
#define LEVEL5_H

#include "Box2D/Box2D.h"
#include <QGraphicsScene>
#include <QWidget>

namespace Ui
{
	class Level5;
}

class Level5 : public QWidget
{
	Q_OBJECT

      public:
	explicit Level5(QWidget *parent = nullptr);
	~Level5();

      private:
	Ui::Level5 *ui;
	void generateMult();
	QString MakeProb();
	void FillChoices();
	void GenerateSolutions();
	bool isCorrect(int num);
	void showCorrect();
	void showWrong();
	void plusScore();
	void punishTime();
	void moveToFinal();
	void makeAndPlaceLine();
	void setUpWorld();
	void showProperLines();
	void showAllLines();
	void explode();

	b2World world;
	b2BodyDef bodyDef[16];
	b2Body *body[16];

	QGraphicsLineItem *line[16];
	QString time;
	QTimer *timer;
	QList<int> posSols;
	int nums[4];
	int first;
	int second;
	int solution;
	int score = 0;
	int frames = 0;
	QGraphicsScene scene;

      signals:
	void returnToSelectClicked();

      private slots:
	void on_levelButton_clicked();
	void on_StartGameBtn_clicked();
	void on_levelButton_3_clicked();
	void on_TutorialResetBtn_clicked();
	void on_AnswerBtn_0_clicked();
	void on_AnswerBtn_1_clicked();
	void on_AnswerBtn_2_clicked();
	void on_AnswerBtn_3_clicked();
	void showTime();
	void updateWorld();
	void resetLines();
	void on_levelselectBtn_clicked();
};

#endif // LEVEL5_H
