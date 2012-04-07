#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "Tile.h"

class Level{
	//float2 *basePosition;
	Tile ***tiles;
	char spriteIDs[8];
	int sizex;
	int sizey;
	std::string filename;
public:
	Level(std::string f);
	char* getSpriteIDs();
	//Tile*** getTiles();
	int getSizeX();
	int getSizeY();
	void printTileInfo();
	Tile* tileAt(int x, int y);
	//Tile* tileAtRel(int x, int y);

};

#endif