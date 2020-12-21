#include "level4square.h"
#include <QGraphicsScene>
#include <iostream>
#include <random>

Level4Square::Level4Square(b2World *world, int xPosPx, float _ppm)
    : QObject(), QGraphicsRectItem()
{
	/* Store box2d world in class variable for later use */
	this->world = world;
	this->PPM = _ppm;

	int r = getRandomColorValue();
	int g = getRandomColorValue();
	int b = getRandomColorValue();

	this->setBrush(QColor(r, g, b));

	/* we object we'll get physics data from instead of the image */
	b2PolygonShape rect;
	rect.SetAsBox((35 / _ppm) / 2, (35 / _ppm) / 2);
	this->setRect(0, 0, 35, 35);
	b2FixtureDef def;
	def.shape = &rect;
	def.density = 9.0f;
	def.friction = 0.3f;
	def.restitution = 0.5f;
	/* create body */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set((xPosPx + this->boundingRect().width() / 2) / _ppm,
			     0.0);
	this->setX(xPosPx);
	this->body = world->CreateBody(&bodyDef);
	this->body->CreateFixture(&def);
	this->body->SetAwake(true);
}

Level4Square::~Level4Square()
{
	this->body->DestroyFixture(this->fixture);
	this->world->DestroyBody(this->body);
	this->body = nullptr;
	this->world = nullptr;
	this->fixture = nullptr;
}

/* Returns a random color value between 0, 255 */
int Level4Square::getRandomColorValue()
{
	/* Random number generator-helper - obtain a random number from hardware
	 */
	std::random_device rd;
	static std::mt19937 eng(rd()); /* seed the generator */
	std::uniform_int_distribution<> distr(0, 255);
	return distr(eng);
}

void Level4Square::applyImpuse()
{
	b2Vec2 wind(0, 4);
	this->body->ApplyLinearImpulse(wind, this->body->GetWorldCenter(),
				       true);
}

void Level4Square::moveSlot()
{
	b2Vec2 position = this->body->GetPosition();
	this->setX(static_cast<double>(position.x * this->PPM) -
		   this->boundingRect().width() / 2);

	this->setY(static_cast<double>(-position.y * this->PPM) -
		   this->boundingRect().height() / 2);
}
