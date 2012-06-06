#ifndef PLAYER_H
#define PLAYER_H

//#include "Avatar.h"
class Avatar;
class Engine;
#include <vector>
#include <SDL.h>

class Player{
	Avatar *avatar;
	int score;
	Engine* engine;
public:
	Player(Engine *e, std::vector<std::string> &filenames, int x=0, int y=0);
	void keyPressed(SDL_Event &e);
	Avatar* getAvatar();
};

#endif