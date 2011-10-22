#ifndef LEVEL_H
#define LEVEL_H

#include <string>

class Level{
	char **tileIDs;
	char spriteIDs[8];
	int sizex;
	int sizey;
	std::string filename;
public:
	Level(std::string f);
	char* getSpriteIDs();
	char** getTileIDs();
	int getSizeX();
	int getSizeY();
};

#endif