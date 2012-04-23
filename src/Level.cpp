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

// Simplified Bresenham algorithm
// http://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
std::vector<Tile*>& Level::getTilesOnLine(int x0, int y0, int x1, int y1){
	std::vector<Tile*> *result = new std::vector<Tile*>();

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);

	int sx, sy;
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	int err = dx - dy;

	result->push_back(tileAt(x0,y0));
	while( x0 != x1 || y0 != y1 ){
		int e2 = err * 2;
		
		if( e2 > -dy ){
			err -= dy;
			x0 += sx;
		}

		if( e2 < dx ){
			err += dx;
			y0 += sy;
		}
		result->push_back(tileAt(x0,y0));
	}
	return *result;
}