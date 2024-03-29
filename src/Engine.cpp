#include "Engine.h"
#include "SceneManager.h"
#include "Player.h"
#include "Mob.h"
#include "Utility.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Level.h"
#include "Tile.h"
#include "Viewport.h"
#include "Pointer.h"

// TEMPORARY HOLDING //
int xpos = 20;
int ypos = 20;
///////////////////////

Engine::Engine(){
	running = false;
	screen = NULL;
	current_scene = NULL;
	num_entities = 0;
	num_characters = 0;

	//Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

	//Set up the screen
    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );

	if( screen != NULL )
		current_scene = new SceneManager(this, screen);

	std::vector<std::string> *filenames = new std::vector<std::string>();
	filenames->push_back("C:\\dev\\games\\media\\guy.png");
	player = new Player(this, *filenames, TILESIZE*10, TILESIZE*10);

	srand( time(NULL) );

	//Tile*** tiles = current_scene->getLevel()->getTiles();
	Level *level = current_scene->getLevel();
	mobs = std::vector<Mob*>();
	for(int i=0; i < 3000; i++){
		
		int x = rand() % current_scene->getLevel()->getSizeX();
		int y = rand() % current_scene->getLevel()->getSizeY();
		
		if( !level->tileAt(x,y)->isOccupied() && level->tileAt(x,y)->getType() != tile_type::impassable){
			filenames = new std::vector<std::string>();
			filenames->push_back("C:\\dev\\games\\media\\zombie_idle.png");
			filenames->push_back("C:\\dev\\games\\media\\zombie_seek.png");
			Mob* mob = new Mob(this, *filenames, TILESIZE*x, TILESIZE*y);
			level->tileAt(x,y)->addOccupant(mob);
			mobs.push_back( mob );
		}
	}
	SDL_ShowCursor(0);

	filenames = new std::vector<std::string>();
	filenames->push_back("C:\\dev\\games\\media\\target.png");
	pointer = new Pointer(this, new v2f(0,0), *filenames);
}

void Engine::Shutdown(){

	SDL_Quit();

}

int Engine::getNumCharacters(){
	return num_characters;
}

Avatar** Engine::getCharacters(){
	return characters;
}

void Engine::Run(){

	current_scene->loadScene();

	Uint32 lastT = SDL_GetTicks();
	Uint32 currentT = SDL_GetTicks();
	Uint32 deltaT = 0;

	int x,y;

	running = true;
	while( running == true )
    {
		lastT = currentT;
		currentT = SDL_GetTicks();
		deltaT = currentT - lastT;

		//While there's an event to handle
        while( SDL_PollEvent( &current_event ) )
        {
			//If the user has Xed out the window
            if( current_event.type == SDL_QUIT )
            {
                //Quit the program
                running = false;
            }   

			//If a key was pressed
            if( current_event.type == SDL_KEYDOWN )
            {
				player->keyPressed(current_event);
            }

			if( current_event.type == SDL_MOUSEMOTION )
			{
				//Get the mouse offsets
				x = current_event.motion.x;
				y = current_event.motion.y;
				pointer->setPos((float)x,(float)y);
			}
        }

		current_scene->getViewport()->Update(deltaT);
		// Call Update for each entity
		for(int i=0; i < num_entities; i++)
			entities[i]->Update(deltaT);

		// Draw the scene
		current_scene->drawScene();
		current_scene->drawPlayer(player);
		for(int i=0; i < mobs.size(); i++)
			current_scene->drawMob(mobs[i]);

		// pointer
		current_scene->applySurface(pointer->getPos()[0] - current_scene->getViewport()->getBasePosition()[0]*TILESIZE, 
						pointer->getPos()[1] - current_scene->getViewport()->getBasePosition()[1]*TILESIZE, pointer->getSprite());
		//setPixel(screen, x, y, 0, 255, 0);
		//drawLine(screen, 0,0,200,200);

		//current_scene->getLevel()->processEdges(this->screen, &current_scene->getViewport()->getBasePosition());
		SDL_Flip( screen );
		//current_scene->getLevel()->printTileInfo();

    }
	Shutdown();
}

void Engine::addEntity(Entity *e){
	entities[num_entities++] = e;
}

void Engine::addCharacter(Avatar *a){
	characters[num_characters++] = a;
}

Entity** Engine::getEntities(){
	return entities;
}

int Engine::getNumEntities(){
	return num_entities;
}

SceneManager* Engine::getSceneManager(){
	return current_scene;
}

std::vector<Mob*> Engine::getMobs(){
	return mobs;
}

SDL_Surface* Engine::getScreen(){
	return screen;
}