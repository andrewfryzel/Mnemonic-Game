#ifndef LEVEL2_H
#define LEVEL2_H

#include "l2content/l2enemy.h"
#include "l2content/l2invadersgame.h"
#include "l2dragwidget.h"

#include <QLabel>
#include <QSlider>
#include <QWidget>

#include <Box2D/Box2D.h>

namespace Ui
{
	class Level2;
}

class Level2 : public QWidget
{
	Q_OBJECT

      public:
	explicit Level2(QWidget *parent = nullptr);
	~Level2();
	void load_letterMenu(int);

      private:
	L2InvaderGame *Game;
	Ui::Level2 *ui;
	L2DragWidget *drag;
	int currentLetterSelection;
	int visited;
	int quiz_answer;

	uint64_t Score;

	QLabel *p, *e, *m, *d, *a, *s;

	void updateTimer(QSlider *, int, int);
	void showAnswers(int);
	void quiz_showNextQuestion();
	void quiz_correctAnswer();
	void quiz_wrongAnswer();

      signals:
	void returnToSelectClicked();

      private slots:
	void quiz_checkAnswer(int);
	void load_quizMenu();
	void load_selectLetterMenu();
	void on_levelSelectButton_clicked();
	void on_levelSelectButton_2_clicked();
};

#endif // LEVEL2_H
