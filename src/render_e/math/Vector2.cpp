/* 
 * File:   Vector2.cpp
 * Author: morten
 * 
 * Created on November 12, 2010, 10:49 PM
 */

#include "Vector2.h"
#include <cassert>
#include <iostream>

namespace render_e {
Vector2::Vector2() {
}

Vector2::~Vector2() {
}


const Vector2 Vector2::operator-() const{
	return Vector2(-x,-y);
}

const Vector2 Vector2::operator+(const Vector2 &other) const{
	return Vector2(x+other.x,y+other.y);
}
const Vector2 Vector2::operator-(const Vector2 &other) const{
	return Vector2(x-other.x,y-other.y);
}

const Vector2 Vector2::operator*(const float &other) const{
	return Vector2(x*other,y*other);
}

float Vector2::operator[]  (const int nIndex) const{
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		default:
#ifdef _DEBUG
        std::cerr<<"Error - illegal index "<<nIndex<<std::endl;
		assert(false);
#endif
		return y;
	}
}

float& Vector2::operator[] (const int nIndex){
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		default:
#ifdef _DEBUG
		std::cerr<<"Error - illegal index "<<nIndex<<std::endl;
		assert(false);
#endif
		return y;
	}
}

}
