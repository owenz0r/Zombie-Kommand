#include <fstream>
#include <iostream>
#include "Level.h"
#include "Utility.h"

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

	edgeList = processEdges();
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

std::vector<v2f*>* Level::processEdges(SDL_Surface *screen, v2f *basePos){

	if( tiles != NULL){

		// map of corner points on level
		bool **cornerMap = new bool*[sizex+1];
		for(int i=0; i < sizex+1; i++){
			cornerMap[i] = new bool[sizey+1];
			for(int j=0; j < sizey+1; j++)
				cornerMap[i][j] = false;
		}

		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		// set up edge array and initialize
		bool **edgeMapY = new bool*[sizex];
		for(int i=0; i < sizex; i++){
			edgeMapY[i] = new bool[sizey+1];
			for(int j=0; j < sizey+1; j++)
				edgeMapY[i][j] = false;
		}

		// loop through tiles Y
		for(int x=0; x < sizex; x++){
			for(int y=0; y < sizey; y++){
				// if the current tile is a wall
				if( tileAt(x,y)->getType() == tile_type::impassable ){
					// if previous isnt a wall
					if( y <= 0 || tileAt(x,y-1)->getType() != tile_type::impassable ){
						edgeMapY[x][y] = true;
					}
					// if next isnt a wall
					if( y >= sizey-1 || tileAt(x,y+1)->getType() != tile_type::impassable ){
						edgeMapY[x][y+1] = true;
					}
				}
			}
		}

		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		// set up edge array and initialize
		bool **edgeMapX = new bool*[sizey];
		for(int i=0; i < sizey; i++){
			edgeMapX[i] = new bool[sizex+1];
			for(int j=0; j < sizex+1; j++)
				edgeMapX[i][j] = false;
		}

		
		// loop through tiles X
		for(int y=0; y < sizey; y++){
			for(int x=0; x < sizex; x++){
				// if the current tile is a wall
				if( tileAt(x,y)->getType() == tile_type::impassable ){
					// if previous isnt a wall
					if( x <= 0 || tileAt(x-1,y)->getType() != tile_type::impassable ){
						edgeMapX[y][x] = true;
					}
					// if next isnt a wall
					if( x >= sizex-1 || tileAt(x+1,y)->getType() != tile_type::impassable ){
						edgeMapX[y][x+1] = true;
					}
				}
			}
		}
		
		/////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////

		
		for(int x=0; x < sizex; x++){
			for(int y=0; y < sizey; y++){
				if( edgeMapX[y][x] == true ){
					if( edgeMapY[x][y] == true ) {
						cornerMap[x][y] = true;
					}
					if( edgeMapY[x][y+1] == true ){
						cornerMap[x][y+1] = true;
					}
				}

				if( x < sizex && edgeMapX[y][x+1] == true ){
					if( edgeMapY[x][y] == true ) {
						cornerMap[x+1][y] = true;
					}
					if( edgeMapY[x][y+1] == true ){
						cornerMap[x+1][y+1] = true;
					}
				}
			}
		}


		std::vector<v2f*> *lines = new std::vector<v2f*>();
		// verticle lines
		for(int x=0; x < sizex+1; x++){
			for(int y=0; y < sizey+1; y++){
				if( cornerMap[x][y] ){
					lines->push_back(new v2f(x,y));
				}
			}
		}
		
		// horizontal lines
		for(int y=0; y < sizey+1; y++){
			for(int x=0; x < sizex+1; x++){
				if( cornerMap[x][y] ){
					lines->push_back(new v2f(x,y));
				}
			}
		}

		if( screen && basePos ){
			// draw lines
			for(int i=0; i < lines->size(); i+=2){
				v2f* p1 = lines->at(i);
				v2f* p2 = lines->at(i+1);
				drawLine(screen, ((*p1)[0]-(*basePos)[0])*TILESIZE, ((*p1)[1]-(*basePos)[1])*TILESIZE, ((*p2)[0]-(*basePos)[0])*TILESIZE, ((*p2)[1]-(*basePos)[1])*TILESIZE);
			}
		}
		
		return lines;
		

	} else {
		std::cout << "TILES ARRAY WAS NULL" << std::endl;
		exit(1);
	}

}

std::vector<v2f*>* Level::getEdgeList(){
	return this->edgeList;
}
