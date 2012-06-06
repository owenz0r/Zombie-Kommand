#ifndef LEVEL_H
#define LEVEL_H

#include <string>
//#include "Tile.h"

#include <SDL.h>

#include "cml_config.h"
#include <cml/cml.h>
typedef cml::vector< float, cml::fixed<2> > v2f;


class Tile;

class Level{
	Tile ***tiles;
	char spriteIDs[8];
	int sizex;
	int sizey;
	std::string filename;
	std::vector<v2f*> *edgeList;
	
public:
	Level(std::string f);
	char* getSpriteIDs();
	int getSizeX();
	int getSizeY();
	void printTileInfo();
	Tile* tileAt(int x, int y);
	std::vector<Tile*> &getTilesOnLine(int x1, int y1, int x2, int y2);
	std::vector<v2f*>* getEdgeList();
	std::vector<v2f*>* processEdges(SDL_Surface* screen=NULL, v2f *basePos=NULL);

};

#endif