#ifndef TILE_H
#define TILE_H

#include "Entity.h"
#include <vector>

enum tile_type{
	none = 0,
	impassable = 1
};

class Tile{
	tile_type type;
	float2 pos;
	std::vector<Entity*> occupants;

public:
	Tile(float x, float y, tile_type type);
	int getType();
	Entity** getOccupants();
	int addOccupant(Entity* e);
	int removeOccupant(Entity* e);
	bool getIsOccupied();
};

#endif