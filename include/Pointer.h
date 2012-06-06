#ifndef POINTER_H
#define POINTER_H

#include "Entity.h"
#include "Drawable.h"
//#include "globals.h"

//class Drawable;
//class Entity;

class Pointer : public Drawable, public Entity {

public:
	Pointer(Engine * e, v2f* pos, std::vector<std::string> &sprites);

};

#endif