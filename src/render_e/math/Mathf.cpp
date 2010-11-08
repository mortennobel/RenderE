/* 
 * File:   Mathf.cpp
 * Author: morten
 * 
 * Created on October 31, 2010, 10:23 PM
 */

#include "Mathf.h"

#include <ctime>
#include <cstdlib>
#include "Vector3.h"

namespace render_e {

const float Mathf::PI = 3.1415927f;
const float Mathf::PI_INVERSE = 1.0f/3.1415927f;
const float Mathf::DEGREE_TO_RADIAN = PI*2/360.0f;
const float Mathf::RADIAN_TO_DEGREE = 3600.0f/PI*2;

const float Mathf::EPSILON = 1.0e-5f;
bool Mathf::IsRandomInitialized = false;

// Returns true if point on triangle plane lies inside triangle (3D version)
// Assumes triangle is not degenerate
bool Mathf::IsPointInTriangle( const Vector3& point, const Vector3& P0,
                              const Vector3& P1, const Vector3& P2 ) {

    Vector3 v0 = P1 - P0;
    Vector3 v1 = P2 - P1;
    Vector3 n = v0.Cross(v1);

    Vector3 wTest = v0.Cross(point - P0);
    if ( wTest.Dot(n) < 0.0f ) {
        return false;
    }

    wTest = v1.Cross(point - P1);
    if ( wTest.Dot(n) < 0.0f ) {
        return false;
    }

    Vector3 v2 = P0 - P2;
    wTest = v2.Cross(point - P2);
    if ( wTest.Dot(n) < 0.0f ) {
        return false;
    }

    return true;
}

float Mathf::Rand(){
    if (!Mathf::IsRandomInitialized) {
        srand(static_cast<unsigned int>(time(0)));
        Mathf::IsRandomInitialized = true;
    }
    return rand()/(float)RAND_MAX;
}

float Mathf::Sqrt(float x){
	return sqrt(x);
    //return 1/InvSqrt(x);
}

// Quake Fast Inverse Square Root
// http://www.beyond3d.com/content/articles/8/
float Mathf::InvSqrt( float x ) {
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
	x = x*(1.5f - xhalf*x*x); // add extra precition
    return x;
}
}
