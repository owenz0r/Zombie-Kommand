#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "SDL.h"
#include "globals.h"

//#include "Drawable.h"
//#include "Level.h"
//#include "Mob.h"
//#include "Viewport.h"
//#include "Player.h"
#include <string>

class Engine;
class Drawable;
class Level;
class Viewport;
class Player;
class Mob;
class Moveable;

#include "cml_config.h"
#include <cml/cml.h>
typedef cml::vector< float, cml::fixed<2> > v2f;

class SceneManager{
	Engine *engine;
	Level *level;
	Viewport *viewport;
	SDL_Surface *screen;
	Drawable *sprites[MAXSPRITES];
	int num_sprites;
public:
	SceneManager(Engine *e, SDL_Surface *s);
	bool drawScene();
	bool loadScene();
	void applySurface(int x, int y, SDL_Surface* source);
	void applySurface(v2f &pos, SDL_Surface* source);
	void drawPlayer(Player *player);
	void drawMob(Mob* mob);
	void Update(Uint32 time);
	void updateOccupancy(Moveable* e);
	bool canMoveTo(int x, int y);
	Level* getLevel();
	Viewport* getViewport();
};

#endif