#include "Player.h"
#include "SceneManager.h"
#include "Engine.h"
#include "Avatar.h"
#include "Level.h"
#include "Tile.h"
#include "Viewport.h"

Player::Player(Engine *e, std::vector<std::string> &filenames, int x, int y){

	score = 0;
	avatar = new Avatar(e, filenames, x, y);
	this->engine = e;
	e->addEntity(avatar);
	e->addCharacter(avatar);
	e->getSceneManager()->getLevel()->tileAt(x/TILESIZE,y/TILESIZE)->addOccupant(avatar);
}

void Player::keyPressed(SDL_Event &e){

	if( avatar->isMoving() == false ){
		switch( e.key.keysym.sym )
		{
			case SDLK_UP: avatar->translateY(-1*TILESIZE); break;
			case SDLK_DOWN: avatar->translateY(1*TILESIZE); break;
			case SDLK_LEFT: avatar->translateX(-1*TILESIZE); break;
			case SDLK_RIGHT: avatar->translateX(1*TILESIZE); break;
		}
	}

	if( engine->getSceneManager()->getViewport()->isMoving() == false ){
		switch( e.key.keysym.sym )
		{
			case SDLK_w: this->engine->getSceneManager()->getViewport()->translateY(-1); break;
			case SDLK_s: this->engine->getSceneManager()->getViewport()->translateY(1); break;
			case SDLK_a: this->engine->getSceneManager()->getViewport()->translateX(-1); break;
			case SDLK_d: this->engine->getSceneManager()->getViewport()->translateX(1); break;
		}
	}

}

Avatar* Player::getAvatar(){
	return avatar;
}