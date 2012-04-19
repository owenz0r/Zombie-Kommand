#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "float2.h"
#include "Tile.h"
#include "Level.h"
#include "Moveable.h"

class Viewport : public Moveable{
	float2* basePosition;
	Level* level;
	int screenTilesX;
	int screenTilesY;
	int maxBaseX;
	int maxBaseY;

	bool canMoveTo(int x, int y);
public:
	Viewport(Level* level);
	//virtual void Update(Uint32 time);
	float2* getBasePosition();
	//void moveUp();
	//void moveDown();
	//void moveLeft();
	//void moveRight();

	virtual bool translateX(int x);
	virtual bool translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);

	int getScreenTilesX();
	int getScreenTilesY();
	float2 *getScreenTilesXY();
	Tile* Viewport::tileAtRel(int x, int y);

	bool isMoving();
};

#endif