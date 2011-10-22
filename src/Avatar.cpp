#include "Avatar.h"

Avatar::Avatar(Engine *e, std::string filename, int x, int y) : Drawable(e, filename, x, y){
	moving = false;
	speed = 3.0f;
}

void Avatar::translateX(int x){
	moving = true;
	destx = pos->x + x;
	desty = pos->y;
	stepx = (destx - pos->x) / 1000;
	stepy = 0.0f;
}

void Avatar::translateY(int y){
	moving = true;
	destx = pos->x;
	desty = pos->y + y;
	stepx = 0.0f;
	stepy = (desty - pos->y) / 1000;
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

		if( stepx > 0.0f || stepy > 0.0f ){
			if( pos->x >= destx && pos->y >= desty ){
				moveTo(destx,desty);
				moving = false;
			}
		} else {
			if( pos->x <= destx && pos->y <= desty ){
				moveTo(destx,desty);
				moving = false;
			}
		}


	}
}

float Avatar::getSpeed(){
	return speed;
}

