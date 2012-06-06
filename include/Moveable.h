#ifndef MOVEABLE_H
#define MOVEABLE_H
#include "globals.h"

#include "cml_config.h"
#include <cml/cml.h>
typedef cml::vector< float, cml::fixed<2> > v2f;

class Moveable {

protected:
	bool moving;
	v2f dest;
	float stepx;
	float stepy;
	float speed;
public:
	virtual ~Moveable(){};
	virtual bool translateX(int x) = 0;
	virtual bool translateY(int y) = 0;
	// explicitly set position
	virtual void moveTo(int x, int y) = 0;
	virtual void animateTo(int x, int y) = 0;
	bool isMoving(){ return moving; };
	v2f& getDest(){ return dest; };

};

#endif