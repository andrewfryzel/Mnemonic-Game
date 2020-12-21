#ifndef LEVEL7_H
#define LEVEL7_H

#include <QGraphicsRectItem>
#include <QWidget>

namespace Ui
{
	class Level7;
}

class Level7 : public QWidget, public QGraphicsRectItem
{
	Q_OBJECT

      public:
	explicit Level7(QWidget *parent = nullptr);
	~Level7();
	void keyPressEvent(QKeyEvent *event);
	int flag;
	void startGame();
	void delay(int time);
	void checkContact();

      public slots:
	void UpdateScores();

      signals:
	void returnToSelectClicked();

      private:
	Ui::Level7 *ui;

      private slots:
	void on_levelButton_2_clicked();
	void on_levelButton_clicked();
	void on_pushButton_clicked();
};

#endif // LEVEL7_H
