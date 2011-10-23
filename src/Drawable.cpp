#include "Drawable.h"
#include "SDL_image.h"

Drawable::Drawable(std::string filename) {

	sprite = loadSprite( filename );
}

SDL_Surface *Drawable::loadSprite( std::string filename )
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image
    loadedImage = IMG_Load( filename.c_str() );
    
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
    }
    
    //Return the optimized image
    return optimizedImage;
}

SDL_Surface *Drawable::getSprite(){
	return sprite;
}

void Drawable::Update(Uint32 time){

}