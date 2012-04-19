#include "Viewport.h"
#include "globals.h"

Viewport::Viewport(Level* level){
	this->basePosition = v2f(0,0);
	this->level = level;
	this->screenTilesX = SCREEN_WIDTH / TILESIZE;
	this->screenTilesY = SCREEN_HEIGHT / TILESIZE;
	this->maxBaseX = this->level->getSizeX() - this->screenTilesX;
	this->maxBaseY = this->level->getSizeY() - this->screenTilesY;

	this->moving = false;
	this->dest = v2f(0,0);
	this->moving = false;
	this->speed = 3.0f;
}

v2f& Viewport::getBasePosition(){
	return this->basePosition;
}

bool Viewport::translateY(int y){
	dest[0] = this->basePosition[0];
	dest[1] = this->basePosition[1] + y;
	if( this->canMoveTo(dest[0], dest[1]) ){
		stepy = (dest[1] - this->basePosition[1]) / 1000;
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
	dest[0] = this->basePosition[0] + x;
	dest[1] = this->basePosition[1];
	if( this->canMoveTo(dest[0], dest[1]) ){
		stepx = (dest[0] - this->basePosition[0]) / 1000;
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
v2f Viewport::getScreenTilesXY(){
	return v2f(this->screenTilesX, this->screenTilesY);
}

Tile* Viewport::tileAtRel(int x, int y){
	return this->level->tileAt( this->basePosition[0] + x, this->basePosition[1] + y);
}

void Viewport::Update(Uint32 time){
	if( moving ){
		this->basePosition[0] += time * stepx * speed;
		this->basePosition[1] += time * stepy * speed;

		// if we're moving in positive direction
		if( stepx > 0.0f || stepy > 0.0f ){
			// if we've reached the destination
			if( this->basePosition[0] >= dest[0] && this->basePosition[1] >= dest[1] ){
				this->moveTo(dest[0],dest[1]);
				moving = false;
			}
		} else {
			if( this->basePosition[0] <= dest[0] && this->basePosition[1] <= dest[1] ){
				this->moveTo(dest[0],dest[1]);
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
	this->basePosition[0] = x;
	this->basePosition[1] = y;
}


void Viewport::animateTo(int x, int y){

}

bool Viewport::isMoving(){
	return this->moving;
}