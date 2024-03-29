#ifndef POINTER_H
#define POINTER_H

#include "Entity.h"
#include "Drawable.h"

class Pointer : public Drawable, public Entity {

public:
	Pointer(Engine * e, v2f* pos, std::vector<std::string> &sprites);
	void Update(Uint32 time);
	void draw();
};

#endif