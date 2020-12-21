#include "l2enemy.h"

L2Enemy::L2Enemy()
{
	this->Sprite = QImage(QString(":/images/Alien_2_Enlarged"));
	this->Body.type = b2_dynamicBody;
	/* World size is 32 meters */
	this->Body.position.Set(0, 32);
	this->Body.angle = 0.0;
	this->DefeatedAnimation = false;
	this->Angle = 0;
}

b2BodyDef *L2Enemy::GetBodyDef() { return &(this->Body); }

bool L2Enemy::GetReached() { return this->Reached; }

void L2Enemy::SetReached(bool Reached) { this->Reached = Reached; }

void L2Enemy::SetDefeated(bool Value) { this->DefeatedAnimation = Value; }

bool L2Enemy::GetDefeated() { return this->DefeatedAnimation; }

void L2Enemy::SetLocation(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

void L2Enemy::SetAngle(float Angle) { this->Angle = Angle; }

void L2Enemy::SetSprite(QImage Image) { this->Sprite = Image; }

QImage L2Enemy::GetSprite() { return this->Sprite; }

int L2Enemy::GetX() { return this->X; }

int L2Enemy::GetY() { return this->Y; }

float L2Enemy::GetAngle() { return this->Angle; }

void L2Enemy::Spin(float Amount)
{
	this->BoundBody->ApplyTorque(Amount, true);
	this->SetAngle(this->BoundBody->GetAngle());
}

b2Body *L2Enemy::GetBoundBody() { return this->BoundBody; }

b2FixtureDef *L2Enemy::GetFixture() { return &(this->Fixture); }

void L2Enemy::BindToWorld(b2World *World)
{
	this->BoundBody = World->CreateBody(&(this->Body));
	this->BodyShape.SetAsBox(2.0f, 2.0f);
	this->Fixture.friction = 0;
	this->Fixture.density = .5;
	this->Fixture.shape = &(this->BodyShape);
	this->BoundBody->CreateFixture(&(this->Fixture));
}