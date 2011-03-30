/* 
 * File:   Mathf.cpp
 * Author: morten
 * 
 * Created on October 31, 2010, 10:23 PM
 */

#include "Mathf.h"

#include <ctime>
#include <cstdlib>
#include <glm/gtc/quaternion.hpp>

namespace render_e {

const float Mathf::PI = 3.1415927f;
const float Mathf::PI_INVERSE = 1.0f/3.1415927f;
const float Mathf::DEGREE_TO_RADIAN = PI*2/360.0f;
const float Mathf::RADIAN_TO_DEGREE = 3600.0f/PI*2;

const float Mathf::EPSILON = 1.0e-5f;
bool Mathf::IsRandomInitialized = false;

void Mathf::SetFromEuler(float pitch, float yaw, float roll, glm::quat &rotation){
    // todo find glm replacement
    float cX, cY, cZ, sX, sY, sZ, cYcZ, sYsZ, cYsZ, sYcZ;

    pitch *= 0.5f;
    yaw *= 0.5f;
    roll *= 0.5f;

    cX = cos(pitch);
    cY = cos(yaw);
    cZ = cos(roll);

    sX = sin(pitch);
    sY = sin(yaw);
    sZ = sin(roll);

    cYcZ = cY * cZ;
    sYsZ = sY * sZ;
    cYsZ = cY * sZ;
    sYcZ = sY * cZ;

    rotation.w = cX * cYcZ + sX * sYsZ;
    rotation.x = sX * cYcZ - cX * sYsZ;
    rotation.y = cX * sYcZ + sX * cYsZ;
    rotation.z = cX * cYsZ - sX * sYcZ;
    // todo implement
}

// Returns true if point on triangle plane lies inside triangle (3D version)
// Assumes triangle is not degenerate
bool Mathf::IsPointInTriangle( const glm::vec3& point, const glm::vec3& P0,
                              const glm::vec3& P1, const glm::vec3& P2 ) {

    glm::vec3 v0 = P1 - P0;
    glm::vec3 v1 = P2 - P1;
    glm::vec3 n = glm::cross(v0,v1);

    glm::vec3 wTest = glm::cross(v0,point - P0);
    if ( glm::dot(wTest,n) < 0.0f ) {
        return false;
    }

    wTest = glm::cross(v1,point - P1);
    if ( glm::dot(wTest,n) < 0.0f ) {
        return false;
    }

    glm::vec3 v2 = P0 - P2;
    wTest = glm::cross(v2,point - P2);
    if ( glm::dot(wTest,n) < 0.0f ) {
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
