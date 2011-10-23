#include "Mob.h"
#include "Avatar.h"
#include "globals.h"
#include "SceneManager.h"
#include <math.h>


Mob::Mob(Engine *e, std::string filename, int x, int y) : Entity(e,x,y), Drawable(filename){
	dest = new float2();
	moving = false;
	speed = 1.0f;
	current_state = seek;
	e->addEntity(this);
}

bool Mob::translateX(int x){
	dest->x = pos->x + x;
	dest->y = pos->y;
	if( engine->getSceneManager()->canMoveTo(dest->x, dest->y) ){
		stepx = (dest->x - pos->x) / 1000;
		stepy = 0.0f;
		moving = true;
		engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
}

bool Mob::translateY(int y){
	dest->x = pos->x;
	dest->y = pos->y + y;
	if( engine->getSceneManager()->canMoveTo(dest->x, dest->y) ){
		stepx = 0.0f;
		stepy = (dest->y - pos->y) / 1000;
		moving = true;
		engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
}

void Mob::moveTo(int x, int y){
	pos->x = x;
	pos->y = y;
}

void Mob::animateTo(int x, int y){

}

void Mob::seekBehavior(Uint32 time){

	Avatar** characters = engine->getCharacters();
	int num = engine->getNumCharacters();

	// find closest avatar
	int id = -1;
	float closest = 9999.0f;
	for(int i=0; i < num; i++){
		float2 *charPos = characters[i]->getPos();
		float2 *diff = pos->vectorTo(charPos);
		float dist = diff->getLength();

		/*
		float diffx = characters[i]->getX() - pos->x;
		float diffy = characters[i]->getY() - pos->y;
		float dist = sqrt((diffx*diffx) + (diffy*diffy));
		*/

		if( dist < closest ){
			closest = dist;
			id = i;
		}
	}

	// vector to nearest avatar
	float2 *dir = pos->vectorTo(characters[id]->getPos());

	// normalize
	dir = dir->normalize();

	// move
	// this is really messy, need to rewrite
	// if length of dir is very small then we're probably on the destination tile
	if ( dir->getLength() > 0.001 ){
		// find which direction gets us closest to our destination
		if( abs(dir->x) > abs(dir->y) ){
			// are we moving positive or negative?
			if( dir->x > 0 ){
				// try to move, if we can't, try other axis
				if( !translateX(1*TILESIZE) ){
					// pos or neg
					if( dir->y > 0 ){
						translateY(1*TILESIZE);
					} else {
						translateY(-1*TILESIZE);
					}
				}
			} else {
				if( !translateX(-1*TILESIZE) ){
					if( dir->y > 0 ){
						translateY(1*TILESIZE);
					} else {
						translateY(-1*TILESIZE);
					}
				}
			}
		} else {
			if( dir->y > 0 ){
				if( !translateY(1*TILESIZE) ){
					if( dir->x > 0 ){
						translateX(1*TILESIZE);
					} else {
						translateX(-1*TILESIZE);
					}
				}
			} else {
				if( !translateY(-1*TILESIZE) ){
					if( dir->x > 0 ){
						translateX(1*TILESIZE);
					} else {
						translateX(-1*TILESIZE);
					}
				}
			}
		}
	}

}

void Mob::wanderBehavior(Uint32 time){


}

void Mob::Update(Uint32 time){

	// if the agent is currently in motion
	if( moving ){
		pos->x += time * stepx * speed;
		pos->y += time * stepy * speed;

		// check if we've overshot our target position and explicitly set 
		// our current position if we have
		if( stepx > 0.0f || stepy > 0.0f ){
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
	} else {
		
		switch(current_state){
			case seek : seekBehavior(time);break;
			case wander : wanderBehavior(time);break;
		}

	}

}

float Mob::getSpeed(){
	return speed;
}