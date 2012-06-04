#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <string>
#include <vector>
#include "SDL.h"
//#include "Entity.h"

class Drawable {
	std::vector<SDL_Surface*> *sprites;
	int currentSprite;
	
public:
	Drawable(std::vector<std::string> &filenames);
	Drawable(std::string filename);
	std::vector<SDL_Surface*> *loadSprite( std::vector<std::string> &filenames );
	SDL_Surface *getSprite();
	void setSprite(int i);
	virtual void Update(Uint32 time);
};

#endif