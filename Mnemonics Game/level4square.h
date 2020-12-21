#ifndef LEVEL4SQUARE_H
#define LEVEL4SQUARE_H
#include <Box2D/Box2D.h>
#include <QGraphicsRectItem>

#include <QObject>

class Level4Square : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

      private:
	b2Fixture *fixture = nullptr;
	b2World *world = nullptr;
	float PPM;

      public:
	b2Body *body = nullptr;

      public:
	explicit Level4Square(b2World *world = nullptr, int xPosPx = 0,
			      float _ppm = 0.0);
	~Level4Square();
	void applyImpuse();

      private:
	int getRandomColorValue();
      signals:

      public slots:
	void moveSlot();
};

#endif // LEVEL4SQUARE_H
