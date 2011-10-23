#ifndef MOVEABLE_H
#define MOVEABLE_H

class Moveable {

protected:
	bool moving;
	float2* dest;
	float stepx;
	float stepy;
public:
	
	virtual ~Moveable(){};
	virtual void translateX(int x) = 0;
	virtual void translateY(int y) = 0;
	// explicitly set position
	virtual void moveTo(int x, int y) = 0;
	virtual void animateTo(int x, int y) = 0;
	bool isMoving(){ return moving; };
	float2* getDest(){ return dest; };

};

#endif