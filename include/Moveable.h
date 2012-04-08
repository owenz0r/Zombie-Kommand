#ifndef MOVEABLE_H
#define MOVEABLE_H

class Moveable {

protected:
	bool moving;
	float2* dest;
	float stepx;
	float stepy;
	float speed;
public:
	
	virtual ~Moveable(){};
	virtual bool translateX(int x) = 0;
	virtual bool translateY(int y) = 0;
	// explicitly set position
	virtual void moveTo(int x, int y) = 0;
	virtual void animateTo(int x, int y) = 0;
	bool isMoving(){ return moving; };
	float2* getDest(){ return dest; };

};

#endif