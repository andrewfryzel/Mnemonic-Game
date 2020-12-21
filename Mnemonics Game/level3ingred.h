#ifndef LEVEL3INGRED_H
#define LEVEL3INGRED_H
#include <Box2D/Box2D.h>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <random>
#include <string>

class Level3Ingredient : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
      public:
	Level3Ingredient(b2World *world = nullptr, float _ppm = 0.0,
			 bool _isCorrectItem = false);
	~Level3Ingredient();
	void setLetterAndStart(std::string _letter);
	void createBody();

      public:
	std::string letter;
	bool isCorrectItem;
	b2Body *body = nullptr;
	std::map<std::string, std::string> foodFiles;

      private:
	bool hasCollided = false;
	/* Box2d */
	float PPM;
	b2Fixture *fixture = nullptr;
	b2World *world = nullptr;
	/* Random number generator */
	std::random_device rd; /* obtains a random number from hardware */

      public slots:
	void moveSlot();
	void stopFallSlot(std::string);

      signals:
	void reportCollisionSignal(Level3Ingredient *);
	void foodOutOfBoundsSignal(Level3Ingredient *);
};

#endif // LEVEL3INGRED_H
