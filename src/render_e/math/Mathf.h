/*
 *  RenderE
 *
 *  Created by Morten Nobel-Jørgensen ( http://www.nobel-joergnesen.com/ ) 
 *  License: LGPL 3.0 ( http://www.gnu.org/licenses/lgpl-3.0.txt )
 */

#ifndef MATHF_H
#define	MATHF_H

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


namespace render_e {
class Vector3;


/* Floating point math */
class Mathf {
 public:
    static const float PI;
	static const float PI_INVERSE;
    static const float EPSILON;
	static const float DEGREE_TO_RADIAN;
	static const float RADIAN_TO_DEGREE;
    inline static bool IsZero(float value) {
        return ( fabsf(value) < EPSILON );
    }
    inline static bool IsEqual(float v1, float v2) {
        return IsZero(v1-v2);
    }
    inline static float Abs(float value) {
       return fabsf(value);
    }
    static bool IsPointInTriangle( const glm::vec3& point, const glm::vec3& P0,
                        const glm::vec3& P1, const glm::vec3& P2 );
	/* Return a random value between 0-1 */
    static float Rand();
	
    static float Clamp(float value, float min, float max){
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
    
    static void SetFromEuler(float pitch, float yaw, float roll, glm::quat &rotation);
    
    static void PrintVec4(glm::vec4 v);
    static void PrintMat4(glm::mat4 m);
    
 private:
     Mathf(void) {}
     static bool IsRandomInitialized;
};
}

#endif	/* MATHF_H */

