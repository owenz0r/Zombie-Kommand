#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Tile.h"
#include "Level.h"
#include "Moveable.h"

class Viewport : public Moveable{
	v2f basePosition;
	Level* level;
	int screenTilesX;
	int screenTilesY;
	int maxBaseX;
	int maxBaseY;

	bool canMoveTo(int x, int y);
public:
	Viewport(Level* level);
	v2f& getBasePosition();

	virtual bool translateX(int x);
	virtual bool translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);

	int getScreenTilesX();
	int getScreenTilesY();
	v2f getScreenTilesXY();
	Tile* Viewport::tileAtRel(int x, int y);

	bool isMoving();
};

#endif