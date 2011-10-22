#include "Entity.h"

Entity::Entity(Engine *e, int x, int y){

	engine = e;
	pos = new float2(x,y);

}

float2* Entity::getPos(){
	return pos;
}