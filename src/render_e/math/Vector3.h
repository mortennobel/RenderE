/*
 *  Vector3.h
 *  RenderE
 *
 *  Created by morten on 10/30/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef VECTOR3_H
#define	VECTOR3_H
 

namespace render_e {

// forward declaration
class Vector4;

class Vector3
{
public:
	Vector3(void);
	Vector3(float x, float y, float z)
	:x(x),y(y),z(z){
	}
	Vector3(float *xyz)
	:x(xyz[0]),y(xyz[1]),z(xyz[2]){
	}
	
    Vector3(const Vector4 &vector);
	
	Vector3(const Vector3& p)
	:x(p.x), y(p.y), z(p.z)
	{   // copy constructor
	}
	
	~Vector3(void);
	
	float Dot(const Vector3 &v) const;
	float Length() const;
    float LengthSqr() const;
	void Normalize();
    void NormalizeExact();
	Vector3 Normalized() const;
	Vector3 Cross(const Vector3 &b) const; 
	float Angle(const Vector3 &b) const;
    Vector3 Reflect(const Vector3 &normal) const;
	
	const Vector3 operator+(const Vector3 &other) const;
	const Vector3 operator-(const Vector3 &other) const;
	const Vector3 operator-() const;
	const Vector3 operator*(const float &other) const;
	float& operator[] (const int nIndex);
	float operator[]  (const int nIndex) const;
private:
	float x;
	float y;
	float z;
};

}

#endif
