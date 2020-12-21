#ifndef LEVEL4_H
#define LEVEL4_H
#include "level4square.h"
#include <Box2D/Box2D.h>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QWidget>
#include <vector>

namespace Ui
{
	class Level4;
}

class Level4 : public QWidget
{
	Q_OBJECT

      public:
	explicit Level4(QWidget *parent = nullptr);
	~Level4();
	void updateGameButtons();
	bool containsNum(int);

      private:
	Ui::Level4 *ui;
	bool winTheGame;
	int maxRound;
	int round;
	int seed;
	int stepScore;
	int totalScore;

	b2World *world = nullptr;
	QList<Level4Square *> squares;
	bool startedWorldUpdates;
	QGraphicsScene *scene = nullptr;
	QGraphicsRectItem *ground = nullptr;

	std::vector<int> sequences;
	int score = 0;
	int quadConst;
	int linearConst;
	int Const;

	int centerX;
	int centerY;

	int tutorialStep;
	int introductionStep;

	bool filled;
	bool showPie;

	QRect QuadSquare;
	QRect UpperLinearRectangle;
	QRect LowerLinearRectangle;
	QRect ConstSquare;

	QRandomGenerator random;

      private:
	void createWorld();
	void updateWorld();

      signals:
	void returnToSelectClicked();
	void moveSignal();

      private slots:
	void on_pushButton_clicked();
	void on_levelButton_clicked();
	// void on_helpButton_clicked();

	void showTutorial();
	void showGameplay();
	void endGame();
	void returnToStartScreen();
	void paintEvent(QPaintEvent *event);

	void updateGame();

	void showintroduction();

	void showinstructions();
	void showprologue();

	void showPieShape();

	void showWinMessage();
	void showLoseMessage();
	void on_levelButton_2_clicked();
	void on_nextBtn_clicked();
	void on_startButton_clicked();
	void on_nextBtn_2_clicked();
	void on_nextBtn_3_clicked();
	void on_nextBtn_4_clicked();
	void on_nextBtn_5_clicked();
	void on_nextBtn_6_clicked();
	void on_levelButton_3_clicked();
	void on_levelButton_4_clicked();
	void on_levelButton_5_clicked();
	void on_levelButton_6_clicked();
	void on_levelButton_7_clicked();
	void on_levelButton_8_clicked();
	void on_endGameButton_clicked();
	void on_returnToMenuButton_clicked();
	void on_nextBtn_7_clicked();

      public slots:
	void onLevel4Clicked();
};

#endif // LEVEL4_H
