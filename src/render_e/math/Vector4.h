/*
 *  Vector4.h
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef VECTOR4_H
#define	VECTOR4_H

namespace render_e {

class Vector4
{
public:
	Vector4(void);
	Vector4(float x, float y, float z, float w=0.0)
	:x(x),y(y),z(z),w(w){
	}
	Vector4(float *xyzw)
	:x(xyzw[0]),y(xyzw[1]),z(xyzw[2]), w(xyzw[3]){
	}
	
	Vector4(const Vector4& p)
	:x(p.x), y(p.y), z(p.z), w(p.w)
	{   // copy constructor
	}
	
	~Vector4(void);
		
	float Dot(const Vector4 &v);
	float Length();
	void Normalize();
	Vector4 Normalized() const;
		
	const Vector4 operator+(const Vector4 &other) const;
	const Vector4 operator-(const Vector4 &other) const;
	const Vector4 operator-() const;
	const Vector4 operator*(const float &other) const;
	float& operator[] (const int nIndex);
	float operator[]  (const int nIndex) const;
private:
	float x;
	float y;
	float z;
	float w;
};
}

#endif
