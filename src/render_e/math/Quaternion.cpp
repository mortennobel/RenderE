/* 
 * File:   Quaternion.cpp
 * Author: morten
 * 
 * Created on October 31, 2010, 10:20 PM
 */

#include "Quaternion.h"

#include <cmath>
#include <cstring>
#include <iostream>
#include "Mathf.h"

#include "Vector3.h"
#include "Matrix44.h"


namespace render_e {

// get a rotation matrix out of the quaternion

void Quaternion::GetMatrix(Matrix44 *matrix) const {
    float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

    // set matrix to identity
    memset(matrix, 0, sizeof (Matrix44));
    (*matrix)(3,3) = 1.0f;

    x2 = x + x;
    y2 = y + y;
    z2 = z + z;

    xx = x * x2;
    xy = x * y2;
    xz = x * z2;

    yy = y * y2;
    yz = y * z2;
    zz = z * z2;

    wx = w * x2;
    wy = w * y2;
    wz = w * z2;

    (*matrix)(0,0) = 1.0f - (yy + zz);
    (*matrix)(0,1) = xy - wz;
    (*matrix)(0,2) = xz + wy;

    (*matrix)(1,0) = xy + wz;
    (*matrix)(1,1) = 1.0f - (xx + zz);
    (*matrix)(1,2) = yz - wx;

    (*matrix)(2,0) = xz - wy;
    (*matrix)(2,1) = yz + wx;
    (*matrix)(2,2) = 1.0f - (xx + yy);
}

/*-------------------------------------------------------------------------------
 * Returns the floating-point sine and cosine of the argument
 *-------------------------------------------------------------------------------*/
//inline void SinCos(float a, float& sina, float& cosa) {
//    sina = sinf(a);
//    cosa = cosf(a);

//}

//void Quaternion::SetAngleAxis(const Vector3 &axis, float angle) {
    // if axis of rotation is zero vector, just set to identity quat
//    float length = axis.LengthSquared();
//    if (Mathf::IsZero(length)) {
//        SetIdentity();
//        return;
//    }

    // take half-angle
//    angle *= 0.5f;
//
//    float sintheta, costheta;
//    SinCos(angle, sintheta, costheta);
//
//    float scaleFactor = sintheta / Mathf::Sqrt(length);
//
//    w = costheta;
//    x = scaleFactor * axis.GetX();
//    y = scaleFactor * axis.GetY();
//    z = scaleFactor * axis.GetZ();
//}

Vector3 Quaternion::GetEuler() {
    Vector3 res;
    double r11, r21, r31, r32, r33, r12, r13;
    double q00, q11, q22, q33;
    double tmp;

    q00 = w * w;
    q11 = x * x;
    q22 = y * y;
    q33 = z * z;

    r11 = q00 + q11 - q22 - q33;
    r21 = 2 * (x * y + w * z);
    r31 = 2 * (x * z - w * y);
    r32 = 2 * (y * z + w * x);
    r33 = q00 - q11 - q22 + q33;

    tmp = fabs(r31);
    if (tmp > 0.999999) {
        r12 = 2 * (x * y - w * z);
        r13 = 2 * (x * z + w * y);

        res[0] = 0.0f;
        res[1] = (float) -((Mathf::PI / 2) * r31 / tmp);
        res[2] = (float) atan2(-r12, -r31 * r13);
    } else {
        res[0] = (float) atan2(r32, r33);
        res[1] = (float) asin(-r31);
        res[2] = (float) atan2(r21, r11);
    }
    return res;
}

void Quaternion::SetFromEuler(float pitch, float yaw, float roll) {
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

    w = cX * cYcZ + sX * sYsZ;
    x = sX * cYcZ - cX * sYsZ;
    y = cX * sYcZ + sX * cYsZ;
    z = cX * cYsZ - sX * sYcZ;
}

Quaternion Quaternion::operator *(const Quaternion &q) const {
    Quaternion result;

    result.w = w * q.w - x * q.x - y * q.y - z * q.z;
    result.x = w * q.x + x * q.w + y * q.z - z * q.y;
    result.y = w * q.y + y * q.w + z * q.x - x * q.z;
    result.z = w * q.z + z * q.w + x * q.y - y * q.x;

    return result;
}

void Quaternion::SetIdentity() {
    x = 0.0f;
    y = 0.0;
    z = 0.0;
    w = 1.0;
}

void Quaternion::operator *=(const Quaternion &q) {
    float _x, _y, _z, _w;

    _w = w * q.w - x * q.x - y * q.y - z * q.z;
    _x = w * q.x + x * q.w + y * q.z - z * q.y;
    _y = w * q.y + y * q.w + z * q.x - x * q.z;
    _z = w * q.z + z * q.w + x * q.y - y * q.x;

    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Quaternion Quaternion::Inverse() {
    float norm = w * w + x * x + y * y + z*z;
    // if we're the zero quaternion, just return
    if (Mathf::IsZero(norm))
        return *this;
    float normRecip = 1.0f / norm;
    float w = normRecip * this->w;
    float x = -normRecip * this->x;
    float y = -normRecip * this->y;
    float z = -normRecip * this->z;


    return Quaternion(x, y, z, w);
}
}
