#include "level3.h"
#include "level3player.h"
#include "scorecontext.h"
#include "ui_level3.h"
#include <QFont>
#include <QGraphicsView>
#include <QTimer>
#include <algorithm>
#include <iostream>
#include <level3ingred.h>
#include <string>

/*
 * Make Level 3 QWidget
 */
Level3::Level3(QWidget *parent) : QWidget(parent), ui(new Ui::Level3)
{
	qDebug("l3 constructor");
	ui->setupUi(this);

	/* Setup Box2D World */
	this->world = new b2World(b2Vec2(0.0f, -9.8f));
	this->startedWorldUpdates = false;

	/* Setup QGraphicsView and QGraphicsScene positioning/size */
	/* HACK: Initialize this value so that valgrind is happy. */
	this->scene = new QGraphicsScene();
	this->scene->setSceneRect(0, 0, this->scene_WIDTH, this->main_HEIGHT);
	ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->graphicsView->setFixedSize(this->scene_WIDTH, this->main_HEIGHT);

	/* Edit labels and other widgets */
	ui->timeSlider->setValue(1500);
	ui->gameMessage->setVisible(false);
	ui->gameMessage->setText("");
	ui->gameMessage->setStyleSheet(
	    "font-weight: bold; color: black; font-size:60px");
	ui->gameMessage->setAlignment(Qt::AlignCenter);
	ui->userInput->setAlignment(Qt::AlignCenter);
	ui->questionLabel->setAlignment(Qt::AlignCenter);
	ui->questionLabel->setWordWrap(true);
	ui->questionLabel->setText("");
	ui->quiztimelabel->setWordWrap(true);
	ui->quiztimelabel->setAlignment(Qt::AlignCenter);
	ui->reubenTalk->setText("GET READY...");
	ui->reubenTalk->setAlignment(Qt::AlignCenter);
	ui->reubenTalk->setWordWrap(true);
	ui->scoreLabel->setAlignment(Qt::AlignCenter);
	ui->livesLabel->setAlignment(Qt::AlignCenter);
	ui->tutMsg->setWordWrap(true);
	ui->tutMsg->setAlignment(Qt::AlignCenter);
	ui->helpMsg->setAlignment(Qt::AlignCenter);
	ui->msg->setAlignment(Qt::AlignCenter);
	ui->msg->setWordWrap(true);
	ui->msg_2->setAlignment(Qt::AlignCenter);
	ui->msg_2->setWordWrap(true);
	ui->msg_3->setAlignment(Qt::AlignCenter);
	ui->msg_3->setWordWrap(true);
	ui->levelLabel->setAlignment(Qt::AlignCenter);

	/* Setup intro Reuben character */
	QPixmap reuben_img(":/reuben/images/reuben-serious.png");
	int w = ui->reuben_intro->width();
	int h = ui->reuben_intro->height();
	ui->reuben_intro->setMinimumSize(1, 1);
	ui->reuben_intro->setPixmap(
	    reuben_img.scaled(w, h, Qt::KeepAspectRatio));
	ui->bubble_1->setVisible(false);
	ui->bubble_1->setWordWrap(true);
	ui->bubble_1->setStyleSheet(
	    "border-radius: 10px; background-color: rgb(213, 248, 248); color: "
	    "rgb(85, 87, 83); qproperty-alignment: AlignCenter; border: 1px "
	    "solid rgb(136, 138, 133);font-size:20pt;");

	/* Setup Reuben game character */
	QPixmap reuben_img2(":/reuben/images/reuben-explain.png");
	int w2 = ui->reubenLabel->width();
	int h2 = ui->reubenLabel->height();
	ui->reubenLabel->setMinimumSize(1, 1);
	ui->reubenLabel->setPixmap(
	    reuben_img2.scaled(w2, h2, Qt::KeepAspectRatio));

	/* Setup Reuben quiz character and cheese */
	QPixmap reuben_img3(":/reuben/images/reuben-sit.png");
	int w3 = ui->reubenQuiz->width();
	int h3 = ui->reubenQuiz->height();
	ui->reubenQuiz->setMinimumSize(1, 1);
	ui->reubenQuiz->setPixmap(
	    reuben_img2.scaled(w3, h3, Qt::KeepAspectRatio));
	QPixmap cheese(":/reuben/images/cheese.png");
	int w4 = ui->foodImg->width();
	int h4 = ui->foodImg->height();
	ui->foodImg->setMinimumSize(1, 1);
	ui->foodImg->setPixmap(cheese.scaled(w4, h4, Qt::KeepAspectRatio));

	/* Setup Reuben for tutorial page */
	QPixmap reuben_img4(":/reuben/images/reuben-explain.png");
	int w5 = ui->reubenTut->width();
	int h5 = ui->reubenTut->height();
	ui->reubenTut->setMinimumSize(1, 1);
	ui->reubenTut->setPixmap(
	    reuben_img4.scaled(w5, h5, Qt::KeepAspectRatio));

	/* Setup Reuben for facts page */
	QPixmap reuben_img5(":/reuben/images/reuben-explain.png");
	int w6 = ui->reubenFact->width();
	int h6 = ui->reubenFact->height();
	ui->reubenFact->setMinimumSize(1, 1);
	ui->reubenFact->setPixmap(
	    reuben_img5.scaled(w6, h6, Qt::KeepAspectRatio));
	ui->gameMessage->setText("Press TAB to begin.");

	/* Add help msgs */
	this->helpMsgs[0] = "Press Left/Right Arrow Keys to Move";
	this->helpMsgs[1] = "EARN 10pts for Catching the CORRECT Ingredient";
	this->helpMsgs[2] = "LOSE 1 Life For Missing, LOSE 15 Points For "
			    "Catching the WRONG Item";
	this->helpMsgs[3] = "You Will Be Quizzed in the Real Game";
	this->helpMsgs[4] = "Ready to Play?";
	ui->helpMsg->setWordWrap(true);

	/* Connect timer for falling ingredients + other things */
	connect(&this->foodTimer, SIGNAL(timeout()), this, SLOT(spawnFood()));

	/* Set to default window/game settings */
	ui->graphicsView->show();
	Level3::resetGame();
}

/* Destructor */
Level3::~Level3()
{
	delete ui;
	delete scene;
	delete player;
	delete world;
	this->world = nullptr;
	this->player = nullptr;
	this->scene = nullptr;
	this->ui = nullptr;
}

/* Updates bodies in Box2D world */
void Level3::updateWorld()
{
	if (this->gameIsPaused)
	{
		return;
	}

	else if (this->quizIsActive && ui->timeSlider->value() <= 0)
	{
		ui->gameMessage->setText("Time's Up");
		quizTimer.stop();
		showNextLevel();
		this->quizIsActive = false;
	}

	/* Box2d step to next position */
	if (this->world)
		this->world->Step(1.0 / 60.0, 6,
				  2); /* Fixed timestep and iterations as per
					 box2d documentation */
	emit moveSignal();
	QTimer::singleShot(60, this, &Level3::updateWorld);
}

/* Resets the tutorial and sets game back to intro page
 * as if the game/level was never played.
 */
void Level3::resetGame()
{
	/* Reset */
	ui->bubble_1->setVisible(false);
	this->currLevel = 0;
	this->currPhraseIndex = 0;
	this->score = 0;
	this->lives = 3;
	this->spawnSpeed = this->MAX_SPAWN_INTERVAL;
	this->tutorialActive = false;
	ui->userInput->setText("");
	ui->reubenTalk->setText("GET READY...");
	ui->livesLabel->setText(
	    QString::fromStdString(std::to_string(this->lives)));
	ui->scoreLabel->setText(
	    QString::fromStdString(std::to_string(this->score)));
	ui->levelLabel->setText(
	    QString::fromStdString(std::to_string(this->currLevel + 1)));
	ui->playNowButton->setText("Play Game");

	generateRandomPhrase();
	Level3::endTutorial();

	/* Set to intro page */
	ui->stackedWidget->setCurrentWidget(ui->introPage);
}

/* Resumes a game and redraws the players on the screen */
void Level3::drawGame()
{
	ui->stackedWidget->setCurrentWidget(ui->gamePage);
	this->gameIsPaused = false;
	ui->userInput->setText("");
	ui->gameMessage->show();
	/* Add Player (bottom sandwich slice) Item */
	this->player = new Level3Player(this->world, this->PPM);
	connect(this->player, &Level3Player::reportCaughtItemSignal, this,
		&Level3::reportCaughtItemSlot);
	this->player->setFlag(QGraphicsItem::ItemIsFocusable);
	this->player->setFocus();
	this->scene->addItem(player);
	/* Fix player positioning and size */
	this->player->setPos(ui->graphicsView->width() / 2 -
				 this->player->boundingRect().width() / 2,
			     ui->graphicsView->height() -
				 (this->player->boundingRect().height() + 25));
	this->player->setHighestY(this->player->y());
	/* Start foodTimer and world simulation */
	this->foodTimer.start(this->spawnSpeed);
	if (!this->startedWorldUpdates)
	{ /* Make sure we only have one timer going */
		QTimer::singleShot(30, this, &Level3::updateWorld);
		this->startedWorldUpdates = true;
	}
}

/* Sets up tutorial that shows how mnemonic memorization
 * And how to create a custom mnemonic using this game
 */
void Level3::showTutorial()
{
	/* Reset some items */
	this->currLevel = 0;
	this->currPhraseIndex = 0;
	this->score = 0;
	this->lives = 3;
	this->tutorialActive = false;
	ui->reubenTalk->setText("Press the right and left arrow keys to move. "
				"Goal: catch and remember them all.");
	ui->livesLabel->setText(
	    QString::fromStdString(std::to_string(this->lives)));
	ui->scoreLabel->setText(
	    QString::fromStdString(std::to_string(this->score)));
	ui->levelLabel->setText(QString::fromStdString("TUTORIAL"));
	ui->helpMsg->setText("Tutorial");
	ui->helpMsg->show();
	ui->gameMessage->setVisible(false);
	this->tutorialActive = true;
	/* Re-arrange existing items*/
	ui->tutorialButton->show();
	ui->tutorialButton->setText("End Tutorial");
	ui->tutorialButton->move(30, 30);
	ui->playNowButton->setVisible(false);
	drawGame();
}

/* Ends Tutorial */
void Level3::endTutorial()
{
	/* Cleanup UI */
	Level3::clearScene();
	ui->tutorialButton->move(scene->width() / 2,
				 scene->height() / 2 -
				     ((ui->tutorialButton->height()) * 1.5));
	ui->tutorialButton->show();
	/* Reflect end in data members */
	this->foodTimer.stop();
	this->tutorialActive = false;
	ui->tutorialButton->setText("Start Tutorial");
	ui->helpMsg->setVisible(false);

	/* Show Start Playing button */
	ui->playNowButton->move(scene->width() / 2, scene->height() / 2);
	ui->playNowButton->show();
}

void Level3::showQuizMsgScreen()
{
	clearScene();
	ui->stackedWidget->setCurrentWidget(ui->quizMsgPage);
}

/* Creates a new scene and replaces old one */
void Level3::clearScene()
{
	ui->gameMessage->setVisible(false);
	this->scene = new QGraphicsScene();
	ui->graphicsView->setScene(scene);
	this->scene->setSceneRect(0, 0, this->scene_WIDTH, this->main_HEIGHT);
}

/* Called to create a new food ingredient object */
void Level3::spawnFood()
{
	if (!this->tutorialActive)
		ui->levelLabel->setText(QString::fromStdString(
		    "LEVEL " + std::to_string(this->currLevel + 1)));
	if (this->currPhraseIndex >= this->currPhrase.length())
	{
		this->foodTimer.stop();

		if (this->tutorialActive)
		{
			endTutorial();
			ui->tutorialButton->setVisible(false);
		}
		else
		{
			this->currLevel++;
			if (this->currLevel != 0)
			{

				showQuizMsgScreen(); /* Go here after every
			    level */
				return;
			}
			else
				showNextLevel(); /* If this is level 0 we go
						    straight to game play */
		}
		return;
	}

	char currLetter = this->currPhrase.at(this->currPhraseIndex);

	/* Spawn food and get letter */
	Level3Ingredient *food =
	    new Level3Ingredient(this->world, this->PPM, true);
	connect(food, &Level3Ingredient::foodOutOfBoundsSignal, this,
		&Level3::foodOutOfBoundsSlot);
	connect(food, &Level3Ingredient::reportCollisionSignal, this->player,
		&Level3Player::reportCollisionSlot);
	connect(this->player, &Level3Player::stopFallSignal, food,
		&Level3Ingredient::stopFallSlot);
	connect(this, &Level3::moveSignal, food, &Level3Ingredient::moveSlot);
	food->setLetterAndStart(std::string(1, currLetter));

	/* Spawn a distraction after _ ms */
	QTimer::singleShot(1000, [this, currLetter] {
		if (this->currPhraseIndex >= this->currPhrase.length())
			return;

		char badLetter = currLetter;
		while (badLetter == currLetter)
		{
			badLetter = getRandomLetter();
		}
		Level3Ingredient *food_bad =
		    new Level3Ingredient(this->world, this->PPM, false);
		connect(food_bad, &Level3Ingredient::foodOutOfBoundsSignal,
			this, &Level3::foodOutOfBoundsSlot);
		connect(food_bad, &Level3Ingredient::reportCollisionSignal,
			this->player, &Level3Player::reportCollisionSlot);
		connect(this->player, &Level3Player::stopFallSignal, food_bad,
			&Level3Ingredient::stopFallSlot);
		connect(this, &Level3::moveSignal, food_bad,
			&Level3Ingredient::moveSlot);
		food_bad->setLetterAndStart(std::string(1, badLetter));

		/* Set random x position */
		food_bad->setPos(this->getRandomXPosition(food_bad), -100);
		food_bad->createBody();

		/* Add to scene*/
		this->scene->addItem(food_bad);
	});

	/* Set Rebuens text bubble */
	ui->reubenTalk->setText(QString::fromStdString(
	    food->letter + " is for " +
	    food->foodFiles.find(food->letter)->second + "!"));

	/* Show messages during gameplay */
	if (this->tutorialActive)
	{
		if (currPhraseIndex > 0)
			ui->gameMessage->setText("");
		ui->helpMsg->setText(
		    QString::fromStdString(this->helpMsgs[currPhraseIndex]));
		ui->helpMsg->show();
	}

	std::string msg = food->foodFiles.find(food->letter)->second;
	msg[0] = std::toupper(msg[0]);
	ui->gameMessage->setText(QString::fromStdString(msg));
	ui->gameMessage->show();

	/* Set random x position */
	food->setPos(this->getRandomXPosition(food), -100);
	food->createBody();

	/* Add to scene*/
	this->scene->addItem(food);
	this->currPhraseIndex += 1;
}

/* Show Quiz Screen */
void Level3::showQuizScreen()
{
	clearScene();
	connect(&this->quizTimer, &QTimer::timeout, this, &Level3::updateTimer);
	ui->quiztimelabel->setVisible(true);
	ui->questionLabel->setVisible(false);
	ui->reubenTalk->setText("Think: What did the ingredients look like?");

	ui->timeSlider->setValue(1500);
	ui->stackedWidget->setCurrentWidget(ui->quizPage);
	this->quizIsActive = true;
	this->quizTimer.start(200);
}

/* increases score if player catches food item */
void Level3::reportCaughtItemSlot(Level3Ingredient *item)
{
	if (this->tutorialActive)
		return;
	if (item->isCorrectItem)
	{
		this->score += 15;
		ui->scoreLabel->setText(
		    QString::fromStdString(std::to_string(this->score)));
	}
	else
	{
		this->score -= 20;
		ui->scoreLabel->setText(
		    QString::fromStdString(std::to_string(this->score)));
	}
}

/* Decrements number of lives if player doesn't catch falling food item */
void Level3::foodOutOfBoundsSlot(Level3Ingredient *item)
{
	if (!this->tutorialActive)
	{
		if (item->isCorrectItem)
		{
			this->lives--;
			ui->livesLabel->setText(QString::fromStdString(
			    std::to_string(this->lives)));
			if (this->lives <= 0)
				showGameOver(false);
		}
	}
}

/* Displays game over screen whether win or lose */
void Level3::showGameOver(bool didWin)
{
	ScoreContext::SetScore(2, this->score);
	ui->stackedWidget->setCurrentWidget(ui->gamePage);
	this->gameIsPaused = true;
	this->startedWorldUpdates = false;
	if (didWin)
	{
		ui->gameMessage->setText("YOU WIN");
	}
	else
	{
		ui->gameMessage->setText("GAME OVER");
	}
	ui->helpMsg->setText(
	    QString::fromStdString("SCORE: " + std::to_string(this->score)));
	ui->helpMsg->show();
	this->foodTimer.stop();
	ui->gameMessage->show();
	ui->playNowButton->setText("Play Again?");
	this->currLevel = 0;
	ui->playNowButton->show();
}

/* Returns a random x position for a QGraphicsItem within the window width */
int Level3::getRandomXPosition(QGraphicsItem *item)
{
	/* Random number generator-helper - obtain a random number from hardware
	 */
	//	std::random_device rd;
	static std::mt19937 eng(1729); /* seed the generator */
	std::uniform_int_distribution<> distr(
	    0, static_cast<int>(this->scene->width() -
				item->boundingRect().width()));
	return distr(eng);
}

/* Returns a char* containing random characters from A-Z. The length
is determined by the current level of this game */
void Level3::generateRandomPhrase()
{
	this->currPhrase = "";
	int length = this->MIN_PHRASE_LENGTH + ((this->currLevel - 1) * 2);
	if (length > 6)
		length = 6; /*limit upper bound*/
	for (int i = 0; i < length; i++)
	{
		this->currPhrase += getRandomLetter();
	}
}

/* Returns a random character from A-Z */
char Level3::getRandomLetter()
{
	/* Random number generator-helper - obtain a random number from hardware
	 */
	static std::random_device rd;
	static std::mt19937 eng2(rd()); /* seed the generator */
	std::uniform_int_distribution<> distr(65, 90);
	return static_cast<char>(distr(eng2));
}

/* Called when level 3 is clicked in the level select window */
void Level3::onLevel3Clicked()
{
	Level3::resetGame();
	QTimer::singleShot(500, [this] {
		ui->bubble_1->setText("Hi, I'm Reuben!");
		ui->bubble_1->show();
	});

	QTimer::singleShot(1500, [this] {
		ui->bubble_1->move(ui->bubble_1->x(), ui->bubble_1->y());
		ui->bubble_1->setText("Let's learn how memory works.");
		ui->bubble_1->show();
	});
}

/* When "Start Tutorial" or "End Tutorial" is clicked */
void Level3::on_tutorialButton_clicked()
{
	this->tutorialActive = !this->tutorialActive;
	if (tutorialActive)
	{
		Level3::showTutorial();
	}
	else
	{
		Level3::endTutorial();
	}
}

/* Upon clicking the Play Now button */
void Level3::on_playNowButton_clicked()
{
	ui->tutorialButton->setVisible(false);
	ui->playNowButton->setVisible(false);
	ui->gameMessage->setText("");

	/* Reset */
	this->currLevel = 0;
	this->currPhraseIndex = 0;
	this->spawnSpeed = this->MAX_SPAWN_INTERVAL;
	this->score = 0;
	this->lives = 3;
	ui->livesLabel->setText(
	    QString::fromStdString(std::to_string(this->lives)));
	ui->scoreLabel->setText(
	    QString::fromStdString(std::to_string(this->score)));
	clearScene();
	drawGame();
}

/* Upon clicking the level select button on intro page */
void Level3::on_levelButton_clicked()
{
	Level3::resetGame();
	emit returnToSelectClicked();
}

/* Upon clicking the level select button on the second page */
void Level3::on_selectlevel_button_clicked()
{
	Level3::resetGame();
	emit returnToSelectClicked();
}

/* Upon clicking the start button show the facts/intro page */
void Level3::on_startButton_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->factsPage);
}

/*  Invoked when user changes input on quiz page */
void Level3::on_userInput_textEdited(const QString &arg1)
{
	std::string userPhrase = arg1.QString::toStdString();
	std::transform(userPhrase.begin(), userPhrase.end(), userPhrase.begin(),
		       ::toupper);
	if (this->currPhrase.compare(userPhrase) == 0 &&
	    ui->timeSlider->value() > 0)
	{
		ui->gameMessage->setText("Correct! +25pts");
		this->score += 25;
		ui->scoreLabel->setText(
		    QString::fromStdString(std::to_string(this->score)));
		quizTimer.stop();
		showNextLevel();
	}
	else if (this->currPhrase.compare(userPhrase) != 0 &&
		 ui->timeSlider->value() <= 0)
	{
		ui->gameMessage->setText("Time's Up");
	}
}

/* Updates slider and responds according to input */
void Level3::updateTimer()
{
	ui->timeSlider->setValue(ui->timeSlider->value() - 2);
}

/* Goes to next level in game. Difficulty increases by increasing the phrase
 * length */
void Level3::showNextLevel()
{
	/* Update global score */
	ScoreContext::SetScore(2, this->score);
	if (this->spawnSpeed > 750)
		this->spawnSpeed -= 300;
	if (this->currLevel >= this->MAX_NUM_LEVELS)
	{ /* Reached last level */
		showGameOver(true);
		return;
	}
	this->currPhraseIndex = 0;
	generateRandomPhrase();
	drawGame();
}

/* Goes to next page which is the quiz page */
void Level3::on_nextBtn_clicked() { showQuizScreen(); }

/* go to the next page which is the inital game page */
void Level3::on_nextBtn_3_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->gamePage);
}

/* go to next page which is the tutorial page */
void Level3::on_nextBtn_2_clicked()
{
	ui->stackedWidget->setCurrentWidget(ui->tutorialPage);
}
