#include "SceneManager.h"
#include "SDL_image.h"
#include "Avatar.h"
#include "Player.h"
#include "Mob.h"
#include <fstream>

SceneManager::SceneManager(Engine *e, SDL_Surface *s){

	screen = s;
	num_sprites = 0;
	engine = e;
	level = new Level( "C:\\dev\\games\\levels\\level1.txt" );

}

void SceneManager::drawPlayer(Player *player){
	
	Avatar *avatar = player->getAvatar();
	applySurface(avatar->getPos(), avatar->getSprite());

}

void SceneManager::drawMob(Mob *mob){
	
	applySurface(mob->getPos(), mob->getSprite());

}

void SceneManager::applySurface(float2 *pos, SDL_Surface *source)
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Get the offsets
    offset.x = pos->x;
    offset.y = pos->y;
    
    //Blit the surface
    SDL_BlitSurface( source, NULL, screen, &offset );
}

void SceneManager::applySurface(int x, int y, SDL_Surface *source)
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Get the offsets
    offset.x = x;
    offset.y = y;
    
    //Blit the surface
    SDL_BlitSurface( source, NULL, screen, &offset );
}

bool SceneManager::loadScene(){

	std::ifstream file( "C:\\dev\\games\\levels\\tiles.txt", std::ifstream::in );
	std::string line;
	std::string *tiles;

	int count = 0;
	while( getline( file, line ) != NULL )
		count++;

	tiles = new std::string[count];

	// reset
	file.close();
	file.clear();
	file.open( "C:\\dev\\games\\levels\\tiles.txt", std::ifstream::in );

	// get names for each tile
	for(int i=0; i < count; i++){
		getline( file, line );
		tiles[i] = line.substr(2);
	}

	// load sprites
	std::string tmp = "C:\\dev\\games\\media\\";
	char* level_sprites = level->getSpriteIDs();
	for(int i=0; i < 8; i++){
		if( level_sprites[i] == 1 ){
			sprites[i] = new Drawable(engine, tmp.append(tiles[i]) );
			tmp = "C:\\dev\\games\\media\\";
			num_sprites++;
		}
	}


	return true;
}

bool SceneManager::drawScene(){

	for(int i=0; i < level->getSizeY(); i++){
		for(int j=0; j < level->getSizeX(); j++)
			applySurface(j*TILESIZE, i*TILESIZE, sprites[level->getTileIDs()[i][j]]->getSprite());
	}

	return true;
}