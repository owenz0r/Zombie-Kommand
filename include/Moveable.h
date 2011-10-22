#ifndef MOVEABLE_H
#define MOVEABLE_H

class Moveable{

protected:
	bool moving;
	int destx;
	int desty;
	float stepx;
	float stepy;
public:
	virtual ~Moveable(){};
	virtual void translateX(int x) = 0;
	virtual void translateY(int y) = 0;
	virtual void moveTo(int x, int y) = 0;
	virtual void animateTo(int x, int y) = 0;
	bool isMoving(){ return moving; };
};

#endif