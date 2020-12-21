#include "l2invadersgame.h"

#include <Box2D/Box2D.h>

#include <QImage>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>

#include <chrono>
#include <iostream>
#include <thread>

#define L2_MAX_Y_POS (8)

static uint8_t LastNum = rand();
/* Want *backwards* gravity so they float upwards/ */
static b2Vec2 Gravity(0.0f, 1.0f);
static b2World World(Gravity);

L2InvaderGame::L2InvaderGame(QWidget *parent) : QWidget(parent)
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	this->Reset();
	this->setMinimumSize(L2_MAX_Y_POS * L2_MAX_Y_POS * 4,
			     L2_MAX_Y_POS * L2_MAX_Y_POS * 4);
}

L2InvaderGame::~L2InvaderGame()
{
	for (uint64_t Index = 0; Index < L2_NUM_ENEMIES; ++Index)
	{
		World.DestroyBody(this->Enemies[Index].GetBoundBody());
	}
}

/* Hack: appear random. */
void CalculateNextIndex()
{
	LastNum += 7;
	LastNum *= 3;
	LastNum = pow(LastNum, 5);
	LastNum %= L2_NUM_ENEMIES;
}

void L2InvaderGame::DefeatEnemy()
{
	/* "defeat" one of the enemies */
	uint8_t Index = rand() % L2_NUM_ENEMIES;
	L2Enemy Ref = this->Enemies[Index];
	/* Don't mark invalid quite just yet. */
	Ref.SetDefeated(true);
	/* Ref.SetReached(true); */
	this->Enemies[Index] = Ref;
	this->RunTick();
}

void L2InvaderGame::AdvanceEnemy()
{
	/* "move" one of the enemies */
	uint8_t Index = rand() % L2_NUM_ENEMIES;
	L2Enemy Ref = this->Enemies[Index];
	if (Ref.GetReached())
	{
		return;
	}
	/* Run the animation... */
	int X = Ref.GetX();
	int Y = Ref.GetY() + 1;
	Ref.SetLocation(X, Y);
	this->Enemies[Index] = Ref;
	this->repaint();
	if (Y == L2_MAX_Y_POS)
	{
		emit this->GameOver();
	}
}

void L2InvaderGame::Reset()
{
	for (int Index = 0; Index < L2_NUM_ENEMIES; ++Index)
	{
		L2Enemy Enemy = this->Enemies[Index];
		Enemy.SetLocation(Index, 0);
		Enemy.SetReached(false);
		Enemy.GetBodyDef()->position.Set(Index, 0);
		Enemy.BindToWorld(&World);
		this->Enemies[Index] = Enemy;
	}
}

void L2InvaderGame::RunTick()
{
	int CountDone = 0;
	for (uint8_t Idx = 0; Idx < L2_NUM_ENEMIES; ++Idx)
	{
		L2Enemy *Enemy = &(this->Enemies[Idx]);
		int X = Enemy->GetX();
		if (Enemy->GetDefeated())
		{
			Enemy->SetSprite(
			    QImage(":/images/Alien_4_Enlarged.png"));
			if (Enemy->GetY() < L2_MAX_Y_POS)
			{
				int CurY = Enemy->GetY();
				Enemy->Spin(120.f);
				World.Step(1, 1, 1);
				Enemy->SetLocation(X, CurY + 1);
				std::cout << Enemy->GetAngle() << std::endl;
				QTimer::singleShot(
				    16, this, [this]() { this->RunTick(); });
				this->repaint();
			}
			else
			{
				Enemy->SetReached(true);
				Enemy->SetDefeated(false);
				Enemy->GetBoundBody()->SetActive(false);
			}
		}
		if (Enemy->GetReached())
		{
			++CountDone;
		}
	}
	if (CountDone == L2_NUM_ENEMIES - 1)
	{
		emit Victory();
	}
}

void L2InvaderGame::paintEvent(QPaintEvent *Event)
{
	QPainter CurPainter(this);
	int W = L2_MAX_Y_POS * 4;
	int H = L2_MAX_Y_POS * 4;
	this->setMaximumSize(this->minimumSize());
	for (uint8_t Idx = 0; Idx < L2_NUM_ENEMIES; ++Idx)
	{
		L2Enemy *Enemy = &(this->Enemies[Idx]);
		if (Enemy->GetReached())
		{
			continue;
		}
		QImage FinalImage = Enemy->GetSprite().scaled(W, H);
		int X = Enemy->GetX();
		int Y = Enemy->GetY();

		if (Enemy->GetDefeated())
		{
			float Angle = Enemy->GetAngle();
			QMatrix Matrox;
			Matrox.rotate(Angle);
			FinalImage = FinalImage.transformed(Matrox);
		}
		CurPainter.drawImage(X * W, Y * H, FinalImage);
	}
	Event->accept();
}