#ifndef AVATAR_H
#define AVATAR_H

#include "Drawable.h"
#include "Moveable.h"
#include "Entity.h"

class Avatar : public Entity, public Drawable, public Moveable{
	int health;
public:
	Avatar(Engine *e, std::vector<std::string> &filenames, int x=0, int y=0);
	virtual bool translateX(int x);
	virtual bool translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);
	float getSpeed();
};

#endif
