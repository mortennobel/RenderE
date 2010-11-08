/*
 *  Matrix4x4.h
 *  RenderE
 *
 *  Created by morten on 10/29/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef MATRIX44_H
#define	MATRIX44_H

#include "vector3.h"


namespace render_e {
    
class Matrix44 {
public:
	/**
     *  Creates a matrix with undefined content
	 */
	Matrix44(void);
	Matrix44(const Matrix44& p);
	~Matrix44(void);
	
	const Matrix44 operator+(const Matrix44 &other) const;
	const Matrix44 operator*(const Matrix44 &other) const;
	const Matrix44 operator*(float f) const;
		
	float& operator() (unsigned row, unsigned col);
	float  operator() (unsigned row, unsigned col) const;
	void SetIdentity();
	float *GetReference(){ return m; }
    const Matrix44 Transpose() const; 
	
    static Matrix44 ScaleInverse(const Vector3 t){
        Matrix44 m;
		m.SetIdentity();
        for (int i=0;i<3;i++){
			m(i,i) = 1.0/t[i];
		}
		return m;
    }
    
    static Matrix44 Scale(const Vector3 t){
        Matrix44 m;
		m.SetIdentity();
        for (int i=0;i<3;i++){
			m(i,i) = t[i];
		}
		return m;
    }
    
	static Matrix44 Translate(const Vector3 t){
		Matrix44 m;
        m.SetIdentity();
		for (int i=0;i<3;i++){
			m(i,3) = t[i];
		}
		return m;
	}
private:
	float m[16];
};	

}
#endif
