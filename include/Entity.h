#ifndef ENTITY_H
#define ENTITY_H

#include "Engine.h"

class Entity{
protected:
	Engine* engine;
	v2f pos;
public:
	Entity(Engine *e, int x=0, int y=0);
	virtual void Update(Uint32 time) = 0;
	v2f& getPos();
	float distanceTo(Entity *other);
};

#endif
