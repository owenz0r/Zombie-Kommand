#ifndef TILE_H
#define TILE_H

#include "Entity.h"

enum tile_type{
	none,
	impassable
};

class Tile{
	Tile(float x, float y, tile_type type);

	tile_type type;
	float2 pos;
	Entity *occupants;
};

#endif