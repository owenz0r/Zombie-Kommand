#include "Tile.h"

Tile::Tile(float x, float y, tile_type type){
	this->pos.x = x;
	this->pos.y = y;
	this->type = type;
}

int Tile::getType(){
	return (int)this->type;
}