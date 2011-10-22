#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Entity.h"
#include <string>

class Drawable : public Entity{
	SDL_Surface *sprite;
	
public:
	Drawable(Engine *e, std::string filename, int x=0, int y=0);
	SDL_Surface *loadSprite( std::string filename );
	SDL_Surface *getSprite();
	virtual void Update(Uint32 time);
};

#endif