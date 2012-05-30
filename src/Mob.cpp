#include "Mob.h"
#include "Avatar.h"
#include "globals.h"
#include "SceneManager.h"
#include "Utility.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>


Mob::Mob(Engine *e, std::vector<std::string> &filenames, int x, int y) : Entity(e,x,y), Drawable(filenames){
	dest = v2f(0,0);
	moving = false;
	speed = 1.0f;
	current_state = wander;
	e->addEntity(this);
	awareness = 10;
	srand( time(NULL) );
}

bool Mob::translateX(int x){
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

bool Mob::translateY(int y){
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

void Mob::moveTo(int x, int y){
	pos[0] = x;
	pos[1] = y;
}

void Mob::animateTo(int x, int y){

}

Avatar* Mob::getClosestAvatar(){
	
	Avatar** characters = engine->getCharacters();
	int num = engine->getNumCharacters();

	// find closest avatar
	int id = -1;
	float closest = 9999.0f;
	for(int i=0; i < num; i++){
		v2f &charPos = characters[i]->getPos();
		v2f diff = charPos - pos;
		float dist = diff.length();

		if( dist < closest ){
			closest = dist;
			id = i;
		}
	}
	return characters[id];
}


void Mob::seekBehavior(Uint32 time, Avatar *closest, float closestDist){

	v2f &closestPos = closest->getPos();

	// only chase if character is within awareness range
	v2f toTarget = v2f(0,0);
	if( closestDist < TILESIZE*this->awareness ){
		toTarget = closestPos - pos;
		toTarget = toTarget.normalize();
	}

	//////
	// check surrounding area for other mobs
	/////

	Level* level = engine->getSceneManager()->getLevel();
	v2f surroundingMobs = v2f(0,0);
	
	for( int i=-1; i < 2; i++ ){
		int x = (this->pos[0] / TILESIZE) + i;
		if( x < 0 || x > level->getSizeX()-1 )
			continue;
		for( int j=-1; j < 2; j++){
			int y = (this->pos[1] / TILESIZE) + j;
			if( y < 0 || y > level->getSizeY()-1 )
				continue;
			std::vector<Entity*> occupants = level->tileAt(x,y)->getOccupants();
			if( occupants.size() > 0 ){
				v2f vec = occupants[0]->getPos() - this->pos;
				surroundingMobs[0] += vec[0];
				surroundingMobs[1] += vec[1];
			}
		}
	}
	
	if( surroundingMobs.length() > 0.0f ){
		surroundingMobs[0] *= -1;
		surroundingMobs[1] *= -1;
		surroundingMobs = surroundingMobs.normalize();
	}
	

	v2f dir = v2f(0,0);
	dir[0] = surroundingMobs[0] + toTarget[0];
	dir[1] = surroundingMobs[1] + toTarget[1];
	
	// normalize
	dir = dir.normalize();

	if ( dir.length() > 0.001 ){
		// find which direction gets us closest to our destination
		if( abs(dir[0]) > abs(dir[1]) ){
			// are we moving positive or negative?
			if( dir[0] > 0 ){
				// try to move, if we can't, try other axis
				translateX(1*TILESIZE);
			} else {
				translateX(-1*TILESIZE);
			}
		} else {
			if( dir[1] > 0 ){
				translateY(1*TILESIZE);
			} else {
				translateY(-1*TILESIZE);
			}
		}
	}
	

	

}

void Mob::wanderBehavior(Uint32 time){

	if( !this->isMoving() ){
		int dir = rand() % 512;
		switch(dir){
			case 0 : this->translateX(-1*TILESIZE); break;
			case 1 : this->translateX(1*TILESIZE); break;
			case 2 : this->translateY(-1*TILESIZE); break;
			case 3 : this->translateY(1*TILESIZE); break;
			default : break;
		}
	}
}

void Mob::Update(Uint32 time){

	// if the agent is currently in motion
	if( moving ){
		pos[0] += time * stepx * speed;
		pos[1] += time * stepy * speed;

		// check if we've overshot our target position and explicitly set 
		// our current position if we have
		if( stepx > 0.0f || stepy > 0.0f ){
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
	} else {
		
		// if we're not moving 
		Avatar* closest = this->getClosestAvatar();
		float closestDist = this->distanceTo(closest);

		// check awareness range and vision
		if( closestDist < (TILESIZE*this->awareness) && this->canSee(closest) ){
			this->current_state = seek;
		} else {
			this->current_state = wander;
		}

		switch(current_state){
			case seek : seekBehavior(time, closest, closestDist);break;
			case wander : wanderBehavior(time);break;
		}

	}

}

// very simple check for visibility
bool Mob::canSee(Entity *other){
	Level* level = this->engine->getSceneManager()->getLevel();

	
	std::vector<v2f*>* edgeList = level->getEdgeList();

	for(int i=0; i < edgeList->size(); i+=2){
		v2f p1(this->pos[0]+(TILESIZE/2), this->pos[1]+(TILESIZE/2));
		v2f p2(other->getPos()[0]+(TILESIZE/2), other->getPos()[1]+(TILESIZE/2));
		if( intersectionTest(p1, p2, *edgeList->at(i), *edgeList->at(i+1)) )
			return false;
	}
	//drawLine(this->engine->getScreen(),this->pos[0],this->pos[1],other->getPos()[0],other->getPos()[1]);
	return true;
	
	/*
	// get the tiles from current tile to other
	std::vector<Tile*> tiles = level->getTilesOnLine((int)this->pos[0] / TILESIZE, (int)this->pos[1] / TILESIZE, 
											(int)other->getPos()[0] / TILESIZE, (int)other->getPos()[1] / TILESIZE);

	// currently only things that block vision are impassables
	for(int i=0; i < tiles.size(); i++){
		if( tiles[i]->getType() == tile_type::impassable )
			return false;
	}
	return true;
	*/
}

float Mob::getSpeed(){
	return speed;
}

mob_state Mob::getCurrentState(){
	return current_state;
}