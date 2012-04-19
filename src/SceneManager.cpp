#include "SceneManager.h"
#include "SDL_image.h"
#include "Avatar.h"
#include "Player.h"
#include "Mob.h"
#include "globals.h"
#include <fstream>

SceneManager::SceneManager(Engine *e, SDL_Surface *s){

	screen = s;
	num_sprites = 0;
	engine = e;
	level = new Level( "C:\\dev\\games\\levels\\level1.txt" );
	viewport = new Viewport(level);
}

void SceneManager::drawPlayer(Player *player){
	
	Avatar *avatar = player->getAvatar();
	applySurface(avatar->getPos()[0] - viewport->getBasePosition()[0]*TILESIZE, avatar->getPos()[1] - viewport->getBasePosition()[1]*TILESIZE, avatar->getSprite());

}

void SceneManager::drawMob(Mob *mob){
	
	applySurface(mob->getPos()[0] - viewport->getBasePosition()[0]*TILESIZE, mob->getPos()[1] - viewport->getBasePosition()[1]*TILESIZE, mob->getSprite());

}

void SceneManager::applySurface(v2f &pos, SDL_Surface *source)
{
    //Temporary rectangle to hold the offsets
    SDL_Rect offset;
    
    //Get the offsets
    offset.x = pos[0];
    offset.y = pos[1];
    
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
			sprites[i] = new Drawable(tmp.append(tiles[i]) );
			tmp = "C:\\dev\\games\\media\\";
			num_sprites++;
		}
	}


	return true;
}

bool SceneManager::drawScene(){

	v2f &screenTiles = viewport->getScreenTilesXY();
	v2f &base = viewport->getBasePosition();
	for(int i=base[0]; i < screenTiles[0]+base[0]; i++){
		for(int j=base[1]; j < screenTiles[1]+base[1]; j++)
			applySurface((i - base[0])*TILESIZE, (j - base[1])*TILESIZE, sprites[level->tileAt(i,j)->getType()]->getSprite());
	}

	return true;
}



void SceneManager::Update(Uint32 time){

}

// update the tiles for who's where
// this seems really ugly, there's gotta be a better way
void SceneManager::updateOccupancy(Moveable* m){
	
	if( Entity* e = dynamic_cast<Entity*>(m) ){
		
		int x = (e->getPos()[0] / TILESIZE);
		int y = (e->getPos()[1] / TILESIZE);
		level->tileAt(x,y)->removeOccupant(e);
		
		x = (m->getDest()[0] / TILESIZE);
		y = (m->getDest()[1] / TILESIZE);
		level->tileAt(x,y)->addOccupant(e);
	}
}

bool SceneManager::canMoveTo(int x, int y){
	if( x < 0 || y < 0 || x >= level->getSizeX()*TILESIZE || y >= level->getSizeY()*TILESIZE )
		return false;
	if( level->tileAt(x / TILESIZE, y / TILESIZE)->isOccupied() )
		return false;
	if( level->tileAt(x / TILESIZE, y / TILESIZE)->getType() == tile_type::impassable )
		return false;
	return true;
}

Level* SceneManager::getLevel(){
	return this->level;
}

Viewport* SceneManager::getViewport(){
	return this->viewport;
}