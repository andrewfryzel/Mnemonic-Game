#include <QPixmap>

#include <Box2D/Box2D.h>

#ifndef L2ENEMY_H
#define L2ENEMY_H

typedef struct B2DEnemyContext
{

} B2DEnemyContext;

class L2Enemy
{
      public:
	L2Enemy();

	bool GetReached();
	void SetReached(bool Reached);

	b2BodyDef *GetBodyDef();

      public slots:
	void SetLocation(int X, int Y);
	void SetAngle(float Angle);
	void SetDefeated(bool Value);
	bool GetDefeated();

	int GetX();
	int GetY();
	b2Body *GetBoundBody();
	b2FixtureDef *GetFixture();
	float GetAngle();
	void BindToWorld(b2World *World);
	void Spin(float Amount);

	void SetSprite(QImage Image);
	QImage GetSprite();

      private:
	int X;
	int Y;
	float Angle;
	bool Reached;
	bool DefeatedAnimation;
	QPixmap Content;
	b2BodyDef Body;
	b2Body *BoundBody;
	b2PolygonShape BodyShape;
	b2FixtureDef Fixture;
	QImage Sprite;
};

#endif // L2ENEMY_H