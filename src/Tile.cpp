#include "Tile.h"

Tile::Tile(float x, float y, tile_type type){
	this->pos.x = x;
	this->pos.y = y;
	this->type = type;
	this->occupants = std::vector<Entity*>();
}

int Tile::getType(){
	return (int)this->type;
}

int Tile::addOccupant(Entity* e){
	this->occupants.push_back(e);
	return 0;
}

int Tile::removeOccupant(Entity* e){

	std::vector<Entity*>::iterator it;
	for(it = this->occupants.begin();it < this->occupants.end(); it++){
		if( *it == e ){
			this->occupants.erase(it);
			return 0;
		}
	}
	// return 1 coz we didnt find the element to erase
	return 1;
}

bool Tile::isOccupied(){
	if( this->occupants.size() > 0 ){
		return true;
	} else {
		return false;
	}
}