#include "Engine.h"
#include "SceneManager.h"
#include "Player.h"
#include "Mob.h"

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

	player = new Player(this, "C:\\dev\\games\\media\\guy.png", TILESIZE*10, TILESIZE*10);
	mob = new Mob(this, "C:\\dev\\games\\media\\zombie.png");
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
        }

		// Call Update for each entity
		for(int i=0; i < num_entities; i++)
			entities[i]->Update(deltaT);

		// Draw the scene
		current_scene->drawScene();
		current_scene->drawPlayer(player);
		current_scene->drawMob(mob);

		SDL_Flip( screen );
    }
	Shutdown();
}

void Engine::addEntity(Entity *e){
	entities[num_entities++] = e;
}

void Engine::addCharacter(Avatar *a){
	characters[num_characters++] = a;
}