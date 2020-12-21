#include "level5.h"
#include "scorecontext.h"
#include "ui_level5.h"
#include <QGraphicsLineItem>
#include <QRandomGenerator>
#include <QString>
#include <QTime>
#include <QTimer>
#include <algorithm>

Level5::Level5(QWidget *parent)
    : QWidget(parent), ui(new Ui::Level5), world(b2Vec2(0.0f, 0.0f))
{

	QTime timeLim(0, 2, 0);
	time = timeLim.toString();

	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &Level5::showTime);

	ui->setupUi(this);

	ui->WorldViewEx->setScene(&scene);
	ui->WorldView->setScene(&scene);

	ui->WorldViewEx->setSceneRect(0, 0, 975, 300);
	ui->WorldView->setSceneRect(0, 0, 975, 300);

	ui->WorldViewEx->setFixedSize(981, 321);
	ui->WorldView->setFixedSize(981, 321);

	generateMult();
	ui->ProblemLbl->setText(MakeProb());
	ui->SolutionLbl->setText("= " + QString::number(solution));

	// setting up the lines:
	makeAndPlaceLine();

	showAllLines();
	showProperLines();

	// b2d testing
	setUpWorld();
}

Level5::~Level5() { delete ui; }

void Level5::on_levelButton_clicked()
{
	emit returnToSelectClicked();
	this->score = 0;
}

void Level5::on_levelButton_3_clicked()
{
	emit returnToSelectClicked();
	ui->stackedWidget->setCurrentWidget(ui->page);
	ScoreContext::SetScore(4, this->score);
	this->score = 0;
	this->ui->ScoreLCD->display(this->score);
}

void Level5::on_StartGameBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);
	generateMult();
	ui->ProblemLbl_2->setText(MakeProb());

	showAllLines();
	showProperLines();

	FillChoices();

	// Setting up the timer
	timer->start(1000);
	showTime();
}

void Level5::on_TutorialResetBtn_clicked()
{
	// Generate new numbers for the tutorial, thus generating another stick
	// visualizer.
	explode();

	generateMult();

	showAllLines();
	showProperLines();

	ui->ProblemLbl->setText(MakeProb());
	ui->SolutionLbl->setText("= " + QString::number(solution));

	QTimer::singleShot(2000, this, SLOT(resetLines()));

	// Might want to "explode" the sticks here as well when you get another
	// tutorial example.
}

void Level5::on_AnswerBtn_0_clicked()
{
	if (isCorrect((ui->AnswerBtn_0->text()).toInt()))
	{
		showCorrect();
		plusScore();
	}
	else
	{
		showWrong();
		punishTime();
	}
	explode();

	generateMult();
	ui->ProblemLbl_2->setText(MakeProb());
	ui->ScoreLCD->display(score);

	showAllLines();
	showProperLines();

	QTimer::singleShot(2000, this, SLOT(resetLines()));
	FillChoices();
}

void Level5::on_AnswerBtn_1_clicked()
{
	if (isCorrect((ui->AnswerBtn_1->text()).toInt()))
	{
		showCorrect();
		plusScore();
	}
	else
	{
		showWrong();
		punishTime();
	}
	explode();

	generateMult();
	ui->ProblemLbl_2->setText(MakeProb());
	ui->ScoreLCD->display(score);

	showAllLines();
	showProperLines();

	QTimer::singleShot(2000, this, SLOT(resetLines()));
	FillChoices();
}

void Level5::on_AnswerBtn_2_clicked()
{
	if (isCorrect((ui->AnswerBtn_2->text()).toInt()))
	{
		showCorrect();
		plusScore();
	}
	else
	{
		showWrong();
		punishTime();
	}
	explode();

	generateMult();
	ui->ProblemLbl_2->setText(MakeProb());
	ui->ScoreLCD->display(score);

	showAllLines();
	showProperLines();

	QTimer::singleShot(2000, this, SLOT(resetLines()));
	FillChoices();
}

void Level5::on_AnswerBtn_3_clicked()
{
	if (isCorrect((ui->AnswerBtn_3->text()).toInt()))
	{
		showCorrect();
		plusScore();
	}
	else
	{
		showWrong();
		punishTime();
	}
	explode();

	generateMult();
	ui->ProblemLbl_2->setText(MakeProb());
	ui->ScoreLCD->display(score);

	showAllLines();
	showProperLines();

	QTimer::singleShot(2000, this, SLOT(resetLines()));
	FillChoices();
}

/*Generates two two digit numbers at random
 *Sets the first number, second number, and what the solution is
 */
void Level5::generateMult()
{
	for (int i = 0; i < 4; i++)
	{
		nums[i] = QRandomGenerator::global()->bounded(1, 5);
	}
	first = nums[0] * 10 + nums[1];
	second = nums[2] * 10 + nums[3];
	solution = (nums[0] * 10 + nums[1]) * (nums[2] * 10 + nums[3]);
}

// Converts the numerical values to a string for the labels
QString Level5::MakeProb()
{
	return QString::number(first) + "  *  " + QString::number(second);
}

void Level5::FillChoices()
{
	// generate 4 possible answers: the solution, one close to the solution,
	// one far off, and one to confuse
	GenerateSolutions();
	ui->AnswerBtn_0->setText(QString::number(posSols[3]));
	ui->AnswerBtn_1->setText(QString::number(posSols[2]));
	ui->AnswerBtn_2->setText(QString::number(posSols[1]));
	ui->AnswerBtn_3->setText(QString::number(posSols[0]));
}

void Level5::GenerateSolutions()
{
	// posSols << solution;
	posSols.clear();
	posSols.append(solution);
	posSols.append(solution + QRandomGenerator::global()->bounded(1, 30));
	posSols.append(solution +
		       QRandomGenerator::global()->bounded(100, 500));
	posSols.append(solution - QRandomGenerator::global()->bounded(3, 20));
	std::random_shuffle(posSols.begin(), posSols.end());
}
void Level5::showCorrect()
{
	ui->WorldView->setBackgroundBrush(QBrush(Qt::green, Qt::SolidPattern));
}
void Level5::showWrong()
{
	ui->WorldView->setBackgroundBrush(QBrush(Qt::red, Qt::SolidPattern));
}

bool Level5::isCorrect(int num)
{
	if (solution == num)
		return true;

	return false;
}

void Level5::plusScore()
{
	score += 100;
	ScoreContext::SetScore(4, score);
}

void Level5::punishTime()
{
	QTime curr = QTime::fromString(time);
	time = curr.addSecs(-5).toString();
}

void Level5::showTime()
{

	QTime start(0, 2, 0);
	QTime end(0, 0, 0);
	QTime curr = QTime::fromString(time);
	time = curr.addSecs(-1).toString();
	ui->TimeLCD->display(curr.toString());
	if (curr > start || curr == end)
	{
		moveToFinal();
	}
}

void Level5::moveToFinal()
{
	ui->stackedWidget->setCurrentIndex(2);
	timer->stop();
	QTime timeLim(0, 2, 0);
	time = timeLim.toString();
	ui->FinalScoreLCD->display(score);
}

void Level5::makeAndPlaceLine()
{
	for (int i = 0; i < 16; i++)
	{
		line[i] = new QGraphicsLineItem(0, 0, 200, 200);
		if (i < 4)
		{
			line[i]->setRotation(90);
			// line[i]->setPen(Qt::PenStyle::DotLine);//for visual
			line[i]->setPos(10 * i + 375, 10 * i - 25);
		}
		else if (i >= 4 && i < 8)
		{
			line[i]->setRotation(90);
			// line[i]->setPen(Qt::PenStyle::DashLine);//for visual
			line[i]->setPos(10 * i + 450, 10 * i + 50);
		}
		else if (i >= 8 && i < 12)
		{
			// line[i]->setPen(Qt::PenStyle::DashDotDotLine);//for
			// visual
			line[i]->setPos(10 * i + 100, -10 * i + 200);
		}
		else if (i >= 12 && i < 16)
		{
			// line[i]->setPen(Qt::PenStyle::DashDotLine);//for
			// visual move up & right
			line[i]->setPos(10 * i + 175, -10 * i - 50 + 175);
		}
		scene.addItem(line[i]);
	}
}

void Level5::setUpWorld()
{
	// Construct a world object, which will hold and simulate the rigid
	// bodies.

	// Define the dynamic body. We set its position and call the body
	// factory.
	for (int i = 0; i < 16; i++)
	{
		bodyDef[i].type = b2_dynamicBody;
		if (i < 4)
		{
			bodyDef[i].position.Set(4 + i * 0.1, -0.1 - i * 0.1);
			bodyDef[i].angle = 90;
		}
		else if (i >= 4 && i < 8)
		{
			bodyDef[i].position.Set(4 + i * 0.2, -0.1 - i * 0.2);
			bodyDef[i].angle = 90;
		}
		else if (i >= 8 && i < 12)
		{
			bodyDef[i].position.Set(4 + i * 0.2, -0.1 - i * 0.2);
		}
		else if (i >= 12 && i < 16)
		{
			bodyDef[i].position.Set(4 + i * 0.1, -0.1 - i * 0.1);
		}
		body[i] = world.CreateBody(&bodyDef[i]);
	}

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	for (int i = 0; i < 16; i++)
	{
		body[i]->CreateFixture(&fixtureDef);
	}
}

void Level5::explode()
{
	QTimer::singleShot(0, this,
			   SLOT(updateWorld())); // starts the simulation
}

void Level5::resetLines()
{
	frames = 0;

	for (int i = 0; i < 16; i++)
	{
		delete line[i];
		world.DestroyBody(body[i]);

		line[i] = new QGraphicsLineItem(0, 0, 200, 200);

		if (i < 4)
		{
			line[i]->setRotation(90);
			// line[i]->setPen(Qt::PenStyle::DotLine);//for visual
			line[i]->setPos(10 * i + 375, 10 * i - 25);

			bodyDef[i].position.Set(4 + i * 0.1, -0.1 - i * 0.1);
			bodyDef[i].angle = 90;
		}
		else if (i >= 4 && i < 8)
		{
			line[i]->setRotation(90);
			// line[i]->setPen(Qt::PenStyle::DashLine);//for visual
			line[i]->setPos(10 * i + 450, 10 * i + 50);

			bodyDef[i].position.Set(4 + i * 0.2, -0.1 - i * 0.2);
			bodyDef[i].angle = 90;
		}
		else if (i >= 8 && i < 12)
		{
			// line[i]->setPen(Qt::PenStyle::DashDotDotLine);//for
			// visual
			line[i]->setPos(10 * i + 100, -10 * i + 200);

			bodyDef[i].position.Set(4 + i * 0.2, -0.1 - i * 0.2);
		}
		else if (i >= 12 && i < 16)
		{
			// line[i]->setPen(Qt::PenStyle::DashDotLine);//for
			// visual move up & right
			line[i]->setPos(10 * i + 175, -10 * i - 50 + 175);

			bodyDef[i].position.Set(4 + i * 0.1, -0.1 - i * 0.1);
		}
		body[i] = world.CreateBody(&bodyDef[i]);
		scene.addItem(line[i]);
	}

	showProperLines();

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	for (int i = 0; i < 16; i++)
	{
		body[i]->CreateFixture(&fixtureDef);
	}
}

void Level5::updateWorld()
{
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	if (frames < 30)
	{
		for (int i = 0; i < 8; i++)
		{
			float rand =
			    QRandomGenerator::global()->bounded(4000, 5000);
			body[i]->ApplyForce(b2Vec2(rand + 1000, 0),
					    b2Vec2(0, 0),
					    true); // play with these values to
						   // mess with explosion
		}
		for (int i = 8; i < 16; i++)
		{
			float rand =
			    QRandomGenerator::global()->bounded(4000, 5000);
			body[i]->ApplyForce(b2Vec2(0, 0),
					    b2Vec2(0, rand + 1000),
					    true); // play with these values to
						   // mess with explosion
		}
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.

		for (int i = 0; i < 16; i++)
		{
			b2Vec2 position = body[i]->GetPosition();
			float32 angle = body[i]->GetAngle();

			line[i]->setPos(10 * position.x + 100,
					10 * position.y + 100);
			line[i]->setRotation(10 * angle);
		}

		QTimer::singleShot(60, this, SLOT(updateWorld()));
	}
	frames++;
}

void Level5::showProperLines()
{
	for (int i = 0; i < 16; i++)
	{
		if (i < 4 && i > nums[0] - 1)
		{
			line[i]->setVisible(false);
		}
		else if (i >= 4 && i < 8 && i > 4 + nums[1] - 1)
		{
			line[i]->setVisible(false);
		}
		else if (i >= 8 && i < 12 && i > 8 + nums[2] - 1)
		{
			line[i]->setVisible(false);
		}
		else if (i >= 12 && i < 16 && i > 12 + nums[3] - 1)
		{
			line[i]->setVisible(false);
		}
	}
}

void Level5::showAllLines()
{
	for (int i = 0; i < 16; i++)
	{
		line[i]->setVisible(true);
	}
}

void Level5::on_levelselectBtn_clicked()
{
	this->score = 0;
	emit returnToSelectClicked();
}
