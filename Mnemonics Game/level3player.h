#ifndef LEVEL3PLAYER_H
#define LEVEL3PLAYER_H
#include <Box2D/Box2D.h>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <level3ingred.h>
#include <string>

class Level3Player : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

      private:
	QList<Level3Ingredient *> collidedItems;
	b2Body *body = nullptr;
	b2World *world = nullptr;
	b2Fixture *fixture = nullptr;
	float PPM;
	double highestItemY;

      public:
	Level3Player(b2World *world = nullptr, float _ppm = 0.0);
	~Level3Player();
	void keyPressEvent(QKeyEvent *event);
	void setHighestY(int y);

      signals:
	void stopFallSignal(std::string);
	void reportCaughtItemSignal(Level3Ingredient *item);

      public slots:
	void reportCollisionSlot(Level3Ingredient *item);
};

#endif // LEVEL3PLAYER_H
