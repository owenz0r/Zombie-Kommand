#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include "Tile.h"

class Level{
	Tile ***tiles;
	char spriteIDs[8];
	int sizex;
	int sizey;
	std::string filename;
public:
	Level(std::string f);
	char* getSpriteIDs();
	int getSizeX();
	int getSizeY();
	void printTileInfo();
	Tile* tileAt(int x, int y);
	std::vector<Tile*> &getTilesOnLine(int x1, int y1, int x2, int y2);

};

#endif