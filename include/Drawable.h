#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include "Entity.h"

class Drawable {
	SDL_Surface *sprite;
	
public:
	Drawable(std::string filename);
	SDL_Surface *loadSprite( std::string filename );
	SDL_Surface *getSprite();
	virtual void Update(Uint32 time);
};

#endif