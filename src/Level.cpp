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
	tileIDs = new char*[count];
	while( getline( file, line ) != NULL ){
		tileIDs[i] = new char[line.size()];
		for(int j=0; j < line.size(); j++)
			tileIDs[i][j] = line.at(j) - '0';
		i++;
	}

	sizex = line.size();
	sizey = count;

	// set which sprites are used in this level
	memset(spriteIDs, 0, 8);
	for(int j=0; j < sizey; j++){
		for(int k=0; k < sizex; k++)
			spriteIDs[tileIDs[j][k]] = 1;
	}
}

char* Level::getSpriteIDs(){
	return spriteIDs;
}

char** Level::getTileIDs(){
	return tileIDs;
}

int Level::getSizeX(){
	return sizex;
}

int Level::getSizeY(){
	return sizey;
}