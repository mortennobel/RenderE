/*
 *  Matrix4x4.cpp
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Matrix44.h"

namespace render_e {

Matrix44::Matrix44(void) {
}

Matrix44::Matrix44(const Matrix44& p) {
    for (int i = 0; i < 16; i++) {
        m[i] = p.m[i];
    }
}

Matrix44::~Matrix44(void) {

}

void Matrix44::SetIdentity() {
    for (int i = 0; i < 16; i++) {
        m[i] = i % 5 == 0 ? 1.0f : 0.0f;
    }
}

const Matrix44 Matrix44::Transpose() const{
    Matrix44 res;
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            res(i,j) = (*this)(j,i);
        }
    }
    return res;
}

const Matrix44 Matrix44::operator+(const Matrix44 &other) const {
    Matrix44 result;
    for (int i = 0; i < 16; i++) {
        result.m[i] = m[i] + other.m[i];
    }
    return result;
}

const Matrix44 Matrix44::operator*(const Matrix44 &other) const {
    Matrix44 result;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            result(r, c) = (*this)(r, 0) * other(0, c)+(*this)(r, 1) * other(1, c)+(*this)(r, 2) * other(2, c)+(*this)(r, 3) * other(3, c);
        }
    }
    return result;
}

const Matrix44 Matrix44::operator*(float f) const {
    Matrix44 res(*this);
    for (int i = 0; i < 16; i++) {
        res.m[i] *= f;
    }
    return res;
}

const Vector3 Matrix44::operator*(const Vector3 &other) const{
    Vector3 res;
    res[0] = (0,0)*other[0]+(0,1)*other[1]+(0,2)*other[2];
    res[1] = (1,0)*other[0]+(1,1)*other[1]+(1,2)*other[2];
    res[2] = (2,0)*other[0]+(2,1)*other[1]+(2,2)*other[2];
    return res;
}

float& Matrix44::operator() (unsigned row, unsigned col) {
    return m[row + col * 4];
}

float Matrix44::operator() (unsigned row, unsigned col) const {
    return m[row + col * 4];
}
}