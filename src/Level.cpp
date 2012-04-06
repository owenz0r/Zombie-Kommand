#include <fstream>
#include <iostream>
#include "Level.h"

using namespace std;

Level::Level(std::string f){

	filename = f;
	ifstream file( filename.c_str(), ifstream::in );
	string line;

	// count lines
	getline( file, line );
	int count = 1;
	while( getline( file, line ) != NULL )
		count++;

	// reset
	file.close();
	file.clear();
	file.open( filename.c_str(), ifstream::in );

	// parse
	int i=0;
	tiles = new Tile**[count];
	while( getline( file, line ) != NULL ){
		tiles[i] = new Tile*[line.size()];
		for(unsigned int j=0; j < line.size(); j++){
			tile_type type = (tile_type)(line.at(j) - '0');
			tiles[i][j] = new Tile(i, j, type);
		}
		i++;
	}

	sizex = line.size();
	sizey = count;

	// set which sprites are used in this level
	memset(spriteIDs, 0, 8);
	for(int j=0; j < sizey; j++){
		for(int k=0; k < sizex; k++)
			spriteIDs[tiles[j][k]->getType()] = 1;
	}
}

char* Level::getSpriteIDs(){
	return spriteIDs;
}
/*
Tile*** Level::getTiles(){
	return tiles;
}
*/

int Level::getSizeX(){
	return sizex;
}

int Level::getSizeY(){
	return sizey;
}

Tile* Level::tileAt(int x, int y){
	return this->tiles[y][x];
}

void Level::printTileInfo(){
	std::cout << "-----------------------" << std::endl;
	for( int i=0; i < sizex; i++ ){
		for( int j=0; j <sizey; j++){
			if( tiles[j][i]->isOccupied() )
				std::cout << "(" << i << "," << j << ")" << std::endl;
		}
	}
}