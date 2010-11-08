/*
 *  Vector4.cpp
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector4.h"

#include <cmath>
#include <cassert>
#include <iostream>
#include "Mathf.h"

namespace render_e {
	
using namespace std;
	
Vector4::Vector4(void)
{}
	
	
Vector4::~Vector4(void)
{}
	
float Vector4::Dot(const Vector4 &v){
	return x*v.x+
		y*v.y+
		z*v.z+
		w*v.w;
}
	
float Vector4::Length(){
	return Mathf::Sqrt(x*x+y*y+z*z+w*w);
}
	
void Vector4::Normalize(){
	float lFactor = 1/Length();
	x *= lFactor;
	y *= lFactor;
	z *= lFactor;
	w *= lFactor;
}
	
Vector4 Vector4::Normalized() const{
	Vector4 res(*this);
	res.Normalize();
	return res;
}
	
const Vector4 Vector4::operator-() const{
	return Vector4(-x,-y,-z,-w);
}
	
const Vector4 Vector4::operator+(const Vector4 &other) const{
	return Vector4(x+other.x,y+other.y,z+other.z, w+other.w);
}

const Vector4 Vector4::operator-(const Vector4 &other) const{
	return Vector4(x-other.x,y-other.y,z-other.z, w-other.w);
}
	
const Vector4 Vector4::operator*(const float &other) const{
	return Vector4(x*other,y*other,z*other, w*other);
}
	
float Vector4::operator[]  (const int nIndex) const{
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		case 2: 
			return z;
		case 3:
			return w;
		default:
#ifdef _DEBUG
			cerr<<"Error - illegal index "<<nIndex<<endl;
			assert(false);
#endif
			return z;
	}
}
	
float& Vector4::operator[] (const int nIndex){
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		case 2: 
			return z;
		case 3:
			return w;
		default:
#ifdef _DEBUG
			cerr<<"Error - illegal index "<<nIndex<<endl;
			assert(false);
#endif
			return z;
	}
}
	
}
