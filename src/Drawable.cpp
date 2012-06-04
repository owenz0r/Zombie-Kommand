#include "Drawable.h"
#include "SDL_image.h"
#include <iostream>

Drawable::Drawable(std::vector<std::string> &filenames) {

	sprites = loadSprite( filenames );
	currentSprite = 0;
}

Drawable::Drawable(std::string filename) {

	std::vector<std::string> filenames;
	filenames.push_back(filename);
	sprites = loadSprite( filenames );
	currentSprite = 0;
}

std::vector<SDL_Surface*> *Drawable::loadSprite( std::vector<std::string> &filenames )
{
	std::vector<SDL_Surface*> *sprites = new std::vector<SDL_Surface*>();
	for(int i=0; i < filenames.size(); i++){
		//The image that's loaded
		SDL_Surface* loadedImage = NULL;
	    
		//The optimized image that will be used
		SDL_Surface* optimizedImage = NULL;
	    
		//Load the image
		loadedImage = IMG_Load( filenames[i].c_str() );
	    
		//If the image loaded
		if( loadedImage != NULL )
		{
			//Create an optimized image
			optimizedImage = SDL_DisplayFormat( loadedImage );
	        
			//Free the old image
			SDL_FreeSurface( loadedImage );

			//If the image was optimized just fine
			if( optimizedImage != NULL )
			{
				//Map the color key
				Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0x11, 0x11, 0x11 );
				//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent
				SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey );
			}
			sprites->push_back(optimizedImage);
		}	
	}
    
    //Return the optimized image
    return sprites;
}

SDL_Surface *Drawable::getSprite(){
	return sprites->at(currentSprite);
}

void Drawable::Update(Uint32 time){

}

void Drawable::setSprite(int i){
	if( i >= 0 && i < this->sprites->size() ){
		currentSprite = i;
	} else {
		std::cout << "BAD SPRITE NUMBER" << std::endl;
	}
}