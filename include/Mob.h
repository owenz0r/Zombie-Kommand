#ifndef MOB_H
#define MOB_H

#include "Drawable.h"
#include "Moveable.h"
#include "Entity.h"

enum mob_state{
	seek,
	wander
};

class Mob : public Entity, public Drawable, public Moveable {
	int health;
	float speed;
	mob_state current_state;
	int awareness;
public:
	Mob(Engine *e, std::vector<std::string> &filenames, int x=0, int y=0);
	virtual bool translateX(int x);
	virtual bool translateY(int y);
	virtual void moveTo(int x, int y);
	virtual void animateTo(int x, int y);
	virtual void Update(Uint32 time);
	void seekBehavior(Uint32 time, Avatar* closest, float closestDist);
	void wanderBehavior(Uint32 time);
	float getSpeed();
	Avatar* getClosestAvatar();
	bool canSee(Entity* other);
	mob_state getCurrentState();
};

#endif