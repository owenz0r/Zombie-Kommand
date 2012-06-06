#include "Entity.h"

Entity::Entity(Engine *e, int x, int y){

	engine = e;
	pos = v2f(x,y);

}

v2f& Entity::getPos(){
	return pos;
}

float Entity::distanceTo(Entity *other){
	v2f vec = other->pos - this->pos;
	return vec.length();
}

void Entity::setPos(float x, float y){
	this->pos[0] = x;
	this->pos[1] = y;
}