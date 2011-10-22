#ifndef ENTITY_H
#define ENTITY_H

#include "Engine.h"
#include "float2.h"

class Entity{
protected:
	Engine* engine;
	float2* pos;
public:
	Entity(Engine *e, int x=0, int y=0);
	virtual void Update(Uint32 time) = 0;
	float2* getPos();
};

#endif
