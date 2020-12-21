#ifndef LEVEL3_H
#define LEVEL3_H
#include <Box2D/Box2D.h>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QSlider>
#include <QTimer>
#include <QWidget>
#include <level3player.h>
#include <map>
#include <random>
#include <string>

namespace Ui
{
	class Level3;
}

class Level3 : public QWidget
{
	Q_OBJECT

      private:
	Ui::Level3 *ui = nullptr;
	QGraphicsScene *scene = nullptr;
	Level3Player *player = nullptr;
	int currLevel;
	int score;
	int lives;
	b2World *world = nullptr;
	const float PPM = 120.0f; /* pixels per meter */
	bool startedWorldUpdates;
	bool tutorialActive;
	bool gameIsPaused;
	bool quizIsActive;
	const int scene_WIDTH =
	    1040 - 170; /* total window width minus right panel */
	const int main_HEIGHT = 529;
	QTimer foodTimer;
	QTimer quizTimer;
	const int MAX_SPAWN_INTERVAL = 3500;
	int spawnSpeed = MAX_SPAWN_INTERVAL;
	const int MAX_NUM_LEVELS = 3;
	const int MIN_PHRASE_LENGTH = 5;
	std::string::size_type currPhraseIndex;
	std::string currPhrase;
	std::string helpMsgs[5];

      public:
	explicit Level3(QWidget *parent = nullptr);
	~Level3();

      private:
	void resetGame();
	void showTutorial();
	void endTutorial();
	void clearScene();
	int getRandomXPosition(QGraphicsItem *item);
	char getRandomLetter();
	void generateRandomPhrase();
	void showNextLevel();
	void showGameOver(bool didWin);
	void drawGame();
	void updateWorld();
	void showQuizMsgScreen();
	void showQuizScreen();

      signals:
	void returnToSelectClicked();
	void moveSignal();

      private slots:
	void on_levelButton_clicked();
	//	void on_levelButton_2_clicked();
	void on_startButton_clicked();
	void on_tutorialButton_clicked();
	void onLevel3Clicked();
	void on_selectlevel_button_clicked();
	void on_playNowButton_clicked();
	void on_userInput_textEdited(const QString &arg1);

	void on_nextBtn_clicked();

	void on_nextBtn_3_clicked();

	void on_nextBtn_2_clicked();

      public slots:
	void updateTimer();
	void spawnFood();
	void foodOutOfBoundsSlot(Level3Ingredient *item);
	void reportCaughtItemSlot(Level3Ingredient *item);
};

#endif // LEVEL3_H
