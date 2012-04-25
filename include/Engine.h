#ifndef ENGINE_H
#define ENGINE_H

#include "SDL.h"
#include "globals.h"
#include <vector>

// forward declarations
class SceneManager;
class Player;
class Entity;
class Avatar;
class Mob;

class Engine{
	bool running;
	bool initialized;
	SDL_Surface *screen;
	SDL_Event current_event;
	SceneManager *current_scene;
	Player *player;
	std::vector<Mob*> mobs;
	Avatar *characters[MAXCHARACTERS];
	Entity *entities[MAXENTITIES];
	int num_entities;
	int num_characters;

	
public:
	Engine();
	void Run();
	void Stop();
	void Shutdown();
	void addEntity(Entity* e);
	void addCharacter(Avatar *a);
	Avatar** getCharacters();
	Entity** getEntities();
	int getNumEntities();
	int getNumCharacters();
	SceneManager* getSceneManager();
	std::vector<Mob*> getMobs();
	SDL_Surface* getScreen();
};

#endif
