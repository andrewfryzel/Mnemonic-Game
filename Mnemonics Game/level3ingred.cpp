#include <QGraphicsScene>
#include <QList>
#include <iostream>
#include <level3ingred.h>
#include <level3player.h>

/* Represents a food item that falls from the top of the window and is rmeoved
 * when it reaches the end of the window. The player must catch the food item
 * as it falls and when it touches the player object (bread slice)
 */
Level3Ingredient::Level3Ingredient(b2World *world, float _ppm,
				   bool _isCorrectItem)
    : QObject(), QGraphicsPixmapItem()
{

	this->isCorrectItem = _isCorrectItem;

	/* Store food ingredient image files */
	this->foodFiles["A"] = "avocado";
	this->foodFiles["B"] = "bacon";
	this->foodFiles["C"] = "cheese";
	this->foodFiles["D"] = "doritos";
	this->foodFiles["E"] = "egg";
	this->foodFiles["F"] = "fish-sticks";
	this->foodFiles["G"] = "grapes";
	this->foodFiles["H"] = "ham";
	this->foodFiles["I"] = "italian-sausage";
	this->foodFiles["J"] = "jalepeno";
	this->foodFiles["K"] = "kale";
	this->foodFiles["L"] = "lettuce";
	this->foodFiles["M"] = "macaroni";
	this->foodFiles["N"] = "noodles";
	this->foodFiles["O"] = "onion-rings";
	this->foodFiles["P"] = "pepperoni";
	this->foodFiles["Q"] = "queso-fresco";
	this->foodFiles["R"] = "ramen";
	this->foodFiles["S"] = "spinach";
	this->foodFiles["T"] = "turkey";
	this->foodFiles["U"] = "umeboshi";
	this->foodFiles["V"] = "veal";
	this->foodFiles["W"] = "waffle";
	this->foodFiles["X"] = "xylocarp";
	this->foodFiles["Y"] = "yams";
	this->foodFiles["Z"] = "zucchini";

	/* Store box2d world in class variable for later use */
	this->world = world;
	this->PPM = _ppm;
}

Level3Ingredient::~Level3Ingredient()
{
	this->body->DestroyFixture(this->fixture);
	this->world->DestroyBody(this->body);
	this->body = nullptr;
	this->world = nullptr;
	this->fixture = nullptr;
}

/* Finds the ingredient image starting with that letter and sets this pixmap */
void Level3Ingredient::setLetterAndStart(std::string _letter)
{
	/* Find right image and modify if necessary */
	this->letter = _letter;
	std::string fpath = ":/ingredients/images/" +
			    (this->foodFiles.find(letter)->second) + ".png";
	QPixmap pixmap(QString::fromStdString(fpath));
	if (_letter == "X")
	{
		setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio));
	}
	else
	{
		setPixmap(pixmap.scaled(120, 120, Qt::KeepAspectRatio));
	}
	this->setPos(this->x(), -this->boundingRect().height());
}

/* Create box2d body */
void Level3Ingredient::createBody()
{
	/* we object we'll get physics data from instead of the image */
	b2PolygonShape rect;
	rect.SetAsBox(2, 2);
	b2FixtureDef def;
	def.shape = &rect;
	def.density = 10.0f;
	def.friction = 0.3f;
	def.restitution = 0.0f;
	/* create body */
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0, 0.0);
	this->body = world->CreateBody(&bodyDef);
	b2Fixture *fix = this->body->CreateFixture(&def);
	fix->SetSensor(true);
	this->body->SetAwake(true);
}

/* Move the ingredient a certain distance down the y-axis. Delete when
it exits the window (scene) or 'attach' it to colliding pixmap */
void Level3Ingredient::moveSlot()
{
	if (this->hasCollided)
	{
		return;
	}

	b2Vec2 position = this->body->GetPosition();
	this->setPos(this->x(), static_cast<double>(-position.y * this->PPM));

	/* colides with pixmap object */
	QList<QGraphicsItem *> colliding_items = collidingItems();
	if (colliding_items.size() > 0)
	{
		emit reportCollisionSignal(this);
		return;
	}

	/* exits window */
	if (this->pos().y() > this->scene()->height())
	{
		this->scene()->removeItem(this);
		emit foodOutOfBoundsSignal(this);
		delete this;
	}
}

/* Stops falling motion if collision occurs */
void Level3Ingredient::stopFallSlot(std::string _letter)
{
	if (_letter.compare(this->letter) == 0)
	{
		this->body->SetActive(false);
		this->hasCollided = true;
	}
}
