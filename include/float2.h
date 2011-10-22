#ifndef FLOAT2_H
#define FLOAT2_H

class float2{
public:
	float x;
	float y;
	float2();
	float2(float x, float y);
	float2* vectorTo(float2* f);
	float2* vectorTo(float x, float y);
	float2* normalize();
	float getLength();
};

#endif