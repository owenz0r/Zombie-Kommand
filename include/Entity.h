#ifndef ENTITY_H
#define ENTITY_H

//#include "globals.h"
//#include "Engine.h"
class Engine;

#include "cml_config.h"
#include <cml/cml.h>
typedef cml::vector< float, cml::fixed<2> > v2f;

#include <SDL.h>

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
