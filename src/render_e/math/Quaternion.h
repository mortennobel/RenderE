/* 
 * File:   Quaternion.h
 * Author: morten
 *
 * Created on October 31, 2010, 10:20 PM
 */

#ifndef QUATERNION_H
#define	QUATERNION_H

namespace render_e {

//forward declaration
class Vector3;
class Matrix44;

class Quaternion {
 public:
    float x, y, z, w;

    Quaternion(void) { x=0.0f, y=0.0, z=0.0, w=1.0; }
    Quaternion(float _x, float _y, float _z, float _w) 
        { x=_x; y=_y; z=_z; w=_w; }

	void SetAngleAxis(const Vector3 &axis, float angle);
    
    void GetMatrix(Matrix44 *matrix) const;
	/* rotation in radians */
    void SetFromEuler(float pitch, float yaw, float roll);
    Vector3 GetEuler();
    void SetIdentity();

    Quaternion operator * (const Quaternion &q) const;
    Vector3 operator * (const Vector3 &q) const;
    void operator *= (const Quaternion &q);
	
	Quaternion Inverse() const;
    
    static Quaternion MakeFromEuler(float pitch, float yaw, float roll){
        Quaternion q;
        q.SetFromEuler(pitch, yaw, roll);
        return q;
    }
};
}
#endif	/* QUATERNION_H */

