/*
 *  Vector3.cpp
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Vector3.h"

#include <cmath>
#include <cassert> 
#include <iostream>
#include "Mathf.h"
#include "Vector4.h"

using namespace std;

namespace render_e {

Vector3::Vector3(const Vector4 &vector)
:x(vector[0]), y(vector[1]), z(vector[2])
{}

Vector3::Vector3(void){}


Vector3::~Vector3(void){}

float Vector3::Angle(const Vector3 &b) const{
	Vector3 an = Normalized();
	Vector3 bn = b.Normalized();
	return acos(an.Dot(bn));
}

float Vector3::Dot(const Vector3 &v) const{
	return x*v.x+
	y*v.y+
	z*v.z;
}

Vector3 Vector3::Reflect(const Vector3 &normal) const{
    //R = V - ( 2 * V [dot] N ) N 
    Vector3 v = Normalized();
    Vector3 n = normal.Normalized();
    return v - n*((v*2).Dot(n));
}

float Vector3::LengthSqr() const{
    return x*x+y*y+z*z;
}

float Vector3::Length() const{
	return Mathf::Sqrt(x*x+y*y+z*z);
}

void Vector3::NormalizeExact(){
    double length = 1/sqrt(((double)x)*x+((double)y)*y+((double)z)*z);
    x = (float)(x/length);
    y = (float)(y/length);
    z = (float)(z/length);
}

void Vector3::Normalize(){
    float lengthSqr = LengthSqr();
    if (Mathf::Abs(lengthSqr-1.0)>Mathf::EPSILON){
        float lFactor = 1/Mathf::Sqrt(lengthSqr);
        if (lFactor!=1){
            x *= lFactor;
            y *= lFactor;
            z *= lFactor;
        }
    }
}

Vector3 Vector3::Normalized() const{
	Vector3 res(*this);
	res.Normalize();
	return res;
}

Vector3 Vector3::Cross(const Vector3 &b) const{
	// a × b = (a2b3 − a3b2) i + (a3b1 − a1b3) j + (a1b2 − a2b1) k = (a2b3 − a3b2, a3b1 − a1b3, a1b2 − a2b1).
	float nx = y*b.z - z*b.y; // (a2b3 − a3b2)
	float ny = z*b.x - x*b.z; // (a3b1 − a1b3)
	float nz = x*b.y - y*b.x; // (a1b2 − a2b1)
	return Vector3(nx,ny,nz);
}

const Vector3 Vector3::operator-() const{
	return Vector3(-x,-y,-z);
}

const Vector3 Vector3::operator+(const Vector3 &other) const{
	return Vector3(x+other.x,y+other.y,z+other.z);
}
const Vector3 Vector3::operator-(const Vector3 &other) const{
	return Vector3(x-other.x,y-other.y,z-other.z);
}

const Vector3 Vector3::operator*(const float &other) const{
	return Vector3(x*other,y*other,z*other);
}

float Vector3::operator[]  (const int nIndex) const{
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		case 2: 
			return z;
		default:
#ifdef _DEBUG
                cerr<<"Error - illegal index "<<nIndex<<endl;
		assert(false);
#endif
		return z;
	}
}

float& Vector3::operator[] (const int nIndex){
	switch(nIndex){
		case 0:
			return x;
		case 1:
			return y;
		case 2: 
			return z;
		default:
#ifdef _DEBUG
		cerr<<"Error - illegal index "<<nIndex<<endl;
		assert(false);
#endif
		return z;
	}
}
}
