#include "float2.h"
#include <math.h>

float2::float2(){
	x = 0.0f;
	y = 0.0f;
}

float2::float2(float x, float y){
	this->x = x;
	this->y = y;
}

float float2::getLength(){
	return sqrt(x*x + y*y);
}

float2* float2::normalize(){
	return new float2(x/this->getLength(),y/this->getLength());
}

float2* float2::vectorTo(float2 *f){
	return new float2(f->x - this->x, f->y - this->y);
}

float2* float2::vectorTo(float x, float y){
	return new float2(x - this->x, y - this->y);
}

