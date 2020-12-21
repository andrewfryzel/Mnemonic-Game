#ifndef L2INVADERSGAME_H
#define L2INVADERSGAME_H

#define L2_NUM_ENEMIES (20)

#include "l2content/l2enemy.h"

#include <QWidget>

class L2InvaderGame : public QWidget
{
	Q_OBJECT
      public:
	explicit L2InvaderGame(QWidget *parent = nullptr);
	virtual ~L2InvaderGame() override;

	void paintEvent(QPaintEvent *Event) override;

	void Reset();
	void RunTick();
      signals:
	void GameOver();
	void Victory();

      public slots:
	void DefeatEnemy();
	void AdvanceEnemy();

      private:
	L2Enemy Enemies[L2_NUM_ENEMIES];
};

#endif // L2INVADERSGAME_H