#include "Entity.h"

Entity::Entity(Engine *e, int x, int y){

	engine = e;
	pos = v2f(x,y);

}

v2f& Entity::getPos(){
	return pos;
}

float Entity::distanceTo(Entity *other){
	//v2f &vec = this->pos->vectorTo(other->getPos());
	v2f vec = other->pos - this->pos;
	return vec.length();
}