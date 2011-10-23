#include "Avatar.h"
#include "SceneManager.h"

Avatar::Avatar(Engine *e, std::string filename, int x, int y) : Entity(e,x,y), Drawable(filename){
	dest = new float2();
	moving = false;
	speed = 3.0f;
}

void Avatar::translateX(int x){
	moving = true;
	dest->x = pos->x + x;
	dest->y = pos->y;
	stepx = (dest->x - pos->x) / 1000;
	stepy = 0.0f;
	engine->getSceneManager()->updateOccupancy(this);
}

void Avatar::translateY(int y){
	moving = true;
	dest->x = pos->x;
	dest->y = pos->y + y;
	stepx = 0.0f;
	stepy = (dest->y - pos->y) / 1000;
	engine->getSceneManager()->updateOccupancy(this);
}

void Avatar::moveTo(int x, int y){
	pos->x = x;
	pos->y = y;
}

void Avatar::animateTo(int x, int y){

}

void Avatar::Update(Uint32 time){
	if( moving ){
		pos->x += time * stepx * speed;
		pos->y += time * stepy * speed;

		// if we're moving in positive direction
		if( stepx > 0.0f || stepy > 0.0f ){
			// if we've reached the destination
			if( pos->x >= dest->x && pos->y >= dest->y ){
				moveTo(dest->x,dest->y);
				moving = false;
			}
		} else {
			if( pos->x <= dest->x && pos->y <= dest->y ){
				moveTo(dest->x,dest->y);
				moving = false;
			}
		}


	}
}

float Avatar::getSpeed(){
	return speed;
}

