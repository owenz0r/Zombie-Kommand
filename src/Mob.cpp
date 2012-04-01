#include "Mob.h"
#include "Avatar.h"
#include "globals.h"
#include "SceneManager.h"
//#include "Tile.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>


Mob::Mob(Engine *e, std::string filename, int x, int y) : Entity(e,x,y), Drawable(filename){
	dest = new float2();
	moving = false;
	speed = 1.0f;
	current_state = seek;
	e->addEntity(this);
	awareness = 10;
	srand( time(NULL) );
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

		if( dist < closest ){
			closest = dist;
			id = i;
		}
	}

	float2* tmp = characters[id]->getPos();
	// vector to nearest avatar

	// only chase if character is within awareness range
	float2 *toTarget = new float2();
	if( closest < TILESIZE*this->awareness ){
		toTarget = pos->vectorTo(tmp->x, tmp->y);
		toTarget = toTarget->normalize();
	}

	//////
	// check surrounding area for other mobs
	/////

	//std::vector<Mob*> otherMobs = engine->getSceneManager()->g;
	Level* level = engine->getSceneManager()->getLevel();
	Tile*** tiles = level->getTiles();
	float2* surroundingMobs = new float2();
	
	for( int i=-1; i < 2; i++ ){
		int x = (this->pos->x / TILESIZE) + i;
		if( x < 0 || x > level->getSizeX()-1 )
			continue;
		for( int j=-1; j < 2; j++){
			int y = (this->pos->y / TILESIZE) + j;
			if( y < 0 || y > level->getSizeY()-1 )
				continue;
			std::vector<Entity*> occupants = tiles[y][x]->getOccupants();
			if( occupants.size() > 0 ){
				float2* vec = this->pos->vectorTo(occupants[0]->getPos());
				surroundingMobs->x += vec->x;
				surroundingMobs->y += vec->y;
			}
		}
	}
	
	if( surroundingMobs->getLength() > 0.0f ){
		surroundingMobs->x *= -1;
		surroundingMobs->y *= -1;
		surroundingMobs = surroundingMobs->normalize();
	}
	

	float2 *dir = new float2();
	dir->x = surroundingMobs->x + toTarget->x;
	dir->y = surroundingMobs->y + toTarget->y;
	
	// normalize
	dir = dir->normalize();

	if ( dir->getLength() > 0.001 ){
		// find which direction gets us closest to our destination
		if( abs(dir->x) > abs(dir->y) ){
			// are we moving positive or negative?
			if( dir->x > 0 ){
				// try to move, if we can't, try other axis
				translateX(1*TILESIZE);
			} else {
				translateX(-1*TILESIZE);
			}
		} else {
			if( dir->y > 0 ){
				translateY(1*TILESIZE);
			} else {
				translateY(-1*TILESIZE);
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