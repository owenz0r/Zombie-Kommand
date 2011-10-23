#ifndef AVATAR_H
#define AVATAR_H

#include "Drawable.h"
#include "Moveable.h"

class Avatar : public Entity, public Drawable, public Moveable{
	int health;
	float speed;
public:
	Avatar(Engine *e, std::string filename, int x=0, int y=0);
	virtual void translateX(int x);
	virtual void translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);
	float getSpeed();
};

#endif
