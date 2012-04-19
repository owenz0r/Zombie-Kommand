#include "Viewport.h"
#include "globals.h"

Viewport::Viewport(Level* level){
	this->basePosition = new float2();
	this->level = level;
	this->screenTilesX = SCREEN_WIDTH / TILESIZE;
	this->screenTilesY = SCREEN_HEIGHT / TILESIZE;
	this->maxBaseX = this->level->getSizeX() - this->screenTilesX;
	this->maxBaseY = this->level->getSizeY() - this->screenTilesY;

	this->moving = false;
	this->dest = new float2();
	this->moving = false;
	this->speed = 3.0f;
}

float2* Viewport::getBasePosition(){
	return this->basePosition;
}

bool Viewport::translateY(int y){
	dest->x = this->basePosition->x;
	dest->y = this->basePosition->y + y;
	if( this->canMoveTo(dest->x, dest->y) ){
		stepy = (dest->y - this->basePosition->y) / 1000;
		stepx = 0.0f;
		moving = true;
		//engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
	/*
	this->basePosition->y -= 1.0f;
	if( this->basePosition->y < 0.0f )
		this->basePosition->y = 0.0f;
	return true;
	*/
}	
/*
void Viewport::moveDown(){
	this->basePosition->y += 1.0f;
	if( this->basePosition->y > this->maxBaseY )
		this->basePosition->y = this->maxBaseY;
}
*/
bool Viewport::translateX(int x){
	dest->x = this->basePosition->x + x;
	dest->y = this->basePosition->y;
	if( this->canMoveTo(dest->x, dest->y) ){
		stepx = (dest->x - this->basePosition->x) / 1000;
		stepy = 0.0f;
		moving = true;
		//engine->getSceneManager()->updateOccupancy(this);
	}
	return moving;
	/*
	this->basePosition->x -= 1.0f;
	if( this->basePosition->x < 0.0f )
		this->basePosition->x = 0.0f;
	return true;
	*/
}
/*
void Viewport::moveRight(){
	this->basePosition->x += 1.0f;
	if( this->basePosition->x > this->maxBaseX )
		this->basePosition->x = this->maxBaseX;
}
*/
float2* Viewport::getScreenTilesXY(){
	return new float2(this->screenTilesX, this->screenTilesY);
}

Tile* Viewport::tileAtRel(int x, int y){
	return this->level->tileAt( this->basePosition->x + x, this->basePosition->y + y);
}

void Viewport::Update(Uint32 time){
	if( moving ){
		this->basePosition->x += time * stepx * speed;
		this->basePosition->y += time * stepy * speed;

		// if we're moving in positive direction
		if( stepx > 0.0f || stepy > 0.0f ){
			// if we've reached the destination
			if( this->basePosition->x >= dest->x && this->basePosition->y >= dest->y ){
				this->moveTo(dest->x,dest->y);
				moving = false;
			}
		} else {
			if( this->basePosition->x <= dest->x && this->basePosition->y <= dest->y ){
				this->moveTo(dest->x,dest->y);
				moving = false;
			}
		}


	}
}

bool Viewport::canMoveTo(int x, int y){
	if( x < 0 || y < 0 || x > this->maxBaseX || y > this->maxBaseY )
		return false;
	return true;
}

void Viewport::moveTo(int x, int y){
	this->basePosition->x = x;
	this->basePosition->y = y;
}


void Viewport::animateTo(int x, int y){

}

bool Viewport::isMoving(){
	return this->moving;
}