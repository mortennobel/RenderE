/* 
 * File:   Vector2.h
 * Author: morten
 *
 * Created on November 12, 2010, 10:49 PM
 */

#ifndef VECTOR2_H
#define	VECTOR2_H

namespace render_e {
class Vector2 {
public:
	Vector2(void);
	Vector2(float x, float y)
	:x(x),y(y){
	}
	Vector2(float *xy)
	:x(xy[0]),y(xy[1]){
	}
	
    Vector2(const Vector2& p)
	:x(p.x), y(p.y)
	{   // copy constructor
	}
	
	~Vector2(void);
	
	const Vector2 operator+(const Vector2 &other) const;
	const Vector2 operator-(const Vector2 &other) const;
	const Vector2 operator-() const;
	const Vector2 operator*(const float &other) const;
	float& operator[] (const int nIndex);
	float operator[]  (const int nIndex) const;
    float *Get(){return &x;}
private:
	float x;
	float y;
};
}
#endif	/* VECTOR2_H */

