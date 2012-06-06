#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <SDL.h>

class Avatar;
class Engine;

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