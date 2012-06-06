#include "Avatar.h"
#include "SceneManager.h"
#include "Engine.h"

Avatar::Avatar(Engine *e, std::vector<std::string> &filenames, int x, int y) : Entity(e,x,y), Drawable(filenames){
	dest = v2f(0,0);
	moving = false;
	speed = 3.0f;
}

bool Avatar::translateX(int x){
	dest[0] = pos[0] + x;
	dest[1] = pos[1];
	if( engine->getSceneManager()->canMoveTo(dest[0], dest[1]) ){
		stepx = (dest[0] - pos[0]) / 1000;
		stepy = 0.0f;
		moving = true;
		engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
}

bool Avatar::translateY(int y){
	dest[0] = pos[0];
	dest[1] = pos[1] + y;
	if( engine->getSceneManager()->canMoveTo(dest[0], dest[1]) ){
		stepx = 0.0f;
		stepy = (dest[1] - pos[1]) / 1000;
		moving = true;
		engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
}

void Avatar::moveTo(int x, int y){
	pos[0] = x;
	pos[1] = y;
}

void Avatar::animateTo(int x, int y){

}

void Avatar::Update(Uint32 time){
	if( moving ){
		pos[0] += time * stepx * speed;
		pos[1] += time * stepy * speed;

		// if we're moving in positive direction
		if( stepx > 0.0f || stepy > 0.0f ){
			// if we've reached the destination
			if( pos[0] >= dest[0] && pos[1] >= dest[1] ){
				moveTo(dest[0],dest[1]);
				moving = false;
			}
		} else {
			if( pos[0] <= dest[0] && pos[1] <= dest[1] ){
				moveTo(dest[0],dest[1]);
				moving = false;
			}
		}


	}
}

float Avatar::getSpeed(){
	return speed;
}

