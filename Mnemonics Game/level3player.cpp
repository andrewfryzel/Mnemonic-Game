#include "level3player.h"
#include <QGraphicsScene>
#include <cmath>
#include <iostream>

/* Constructor for Player class that scales the bread slice image */
Level3Player::Level3Player(b2World *world, float _ppm)
    : QObject(), QGraphicsPixmapItem()
{
	/* Store box2d world in class variable for later use */
	this->world = world;
	this->PPM = _ppm;

	QPixmap img(":/ingredients/images/bread-slice.png");
	setPixmap(img.scaled(175, 175, Qt::KeepAspectRatio));

	b2PolygonShape rect;
	float boxW = (this->pixmap().width() / this->PPM) / 2.0f;
	float boxH = (this->pixmap().height() / this->PPM) / 2.0f;

	rect.SetAsBox(boxW, boxH);
	b2FixtureDef def;
	def.shape = &rect;
	def.density = 4.0f;
	def.friction = 0.3f;
	def.restitution = .9f;

	/* create body */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0, 0.0);
	this->body = world->CreateBody(&bodyDef);
	this->body->CreateFixture(&def);
	this->body->SetAwake(true);
}

/* Destructor */
Level3Player::~Level3Player()
{
	this->body->DestroyFixture(this->fixture);
	this->world->DestroyBody(this->body);
	qDeleteAll(collidedItems);
	this->body = nullptr;
	this->world = nullptr;
	this->fixture = nullptr;
}

/* Setter for highest y position of the top item of the sandwich */
void Level3Player::setHighestY(int y) { this->highestItemY = y; }

/* Listens to key press events to move sandwich */
void Level3Player::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Left)
	{
		if (this->x() > 0)
		{
			this->setPos(x() - 10, this->y());
			for (int i = 0; i < this->collidedItems.length(); ++i)
			{
				this->collidedItems[i]->setPos(
				    collidedItems[i]->x() - 10,
				    collidedItems[i]->y());
			}
		}
	}
	else if (event->key() == Qt::Key_Right)
	{
		if ((x() + boundingRect().width()) < scene()->width())
		{
			this->setPos(x() + 10, this->y());
			for (int i = 0; i < this->collidedItems.length(); ++i)
			{
				this->collidedItems[i]->setPos(
				    collidedItems[i]->x() + 10,
				    collidedItems[i]->y());
			}
		}
	}
}

/* Adds a fallen food item to this collidedItems list if the fallen item
is close enough to the center */
void Level3Player::reportCollisionSlot(Level3Ingredient *item)
{
	double itemXCenter = item->x() + (item->boundingRect().width() / 2);
	double itemYCenter = item->y() + (item->boundingRect().height() / 2);
	double playerXCenter = this->x() + (this->boundingRect().width() / 2);
	double playerYCenter = this->y() + (this->boundingRect().height() / 2);
	double d = 90.0;
	double xDistance = abs(itemXCenter - playerXCenter);
	bool isBelowPlayerCenter = itemYCenter > playerYCenter;
	bool isAbovePlayerItems =
	    (item->y() + item->boundingRect().height()) < this->highestItemY;

	if (xDistance < d && !isBelowPlayerCenter && !isAbovePlayerItems)
	{
		/* center the images on the sandwich */
		if (item->letter == "C" || item->letter == "J" ||
		    item->letter == "A" || item->letter == "S" ||
		    item->letter == "D")
		{
			item->setPos(this->x() + 20, item->y() + 15);
		}
		else
		{
			item->setPos(this->x() + 20, item->y() + 5);
		}
		this->collidedItems.append(item);
		if (item->y() > this->highestItemY)
			setHighestY(item->y());
		item->setActive(false);
		emit Level3Player::reportCaughtItemSignal(item);
		emit Level3Player::stopFallSignal(item->letter);
	}
}
