#include "Player.h"
#include "SceneManager.h"

Player::Player(Engine *e, std::string filename, int x, int y){

	score = 0;
	avatar = new Avatar(e, filename, x, y);
	e->addEntity(avatar);
	e->addCharacter(avatar);
	e->getSceneManager()->getLevel()->getTiles()[y/TILESIZE][x/TILESIZE]->addOccupant(avatar);
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

}

Avatar* Player::getAvatar(){
	return avatar;
}