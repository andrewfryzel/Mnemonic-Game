#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <levelselect.h>

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

      public:
	explicit MainWindow(QWidget *parent = nullptr);
	QWidget *myWidget;
	QString widgetStyle;
	~MainWindow();

      private slots:
	void on_startButton_clicked();
	void returnToHome();
	void returnToDefaultBackground();
	void on_homeButton_clicked();

      private:
	Ui::MainWindow *ui;
	LevelSelect SelectLevel;
};

#endif // MAINWINDOW_H
