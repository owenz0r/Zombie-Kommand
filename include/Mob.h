#ifndef MOB_H
#define MOB_H

#include "Drawable.h"
#include "Moveable.h"

enum State{
	seek,
	wander
};

class Mob : public Entity, public Drawable, public Moveable {
	int health;
	float speed;
	State current_state;
public:
	Mob(Engine *e, std::string filename, int x=0, int y=0);
	virtual void translateX(int x);
	virtual void translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);
	void seekBehavior(Uint32 time);
	void wanderBehavior(Uint32 time);
	float getSpeed();
};

#endif