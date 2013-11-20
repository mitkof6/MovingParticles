/*
 * Vector3D.h
 *
 *  Created on: Oct 22, 2013
 *      Author: crow
 */

#ifndef VECTOR3D_H_
#define VECTOR3D_H_

#include <math.h>

#define TOLL 0.00001

class Vector3D {
public:
	float x, y, z;

	Vector3D();
	Vector3D(const Vector3D &other);
	Vector3D(float xx, float yy, float zz);
	virtual ~Vector3D();

	Vector3D operator +(Vector3D other);
	Vector3D operator -(Vector3D other);
	Vector3D operator *(float c);
	Vector3D operator /(float c);

	float dot(Vector3D other);

	float magnitude();
	float magnitudeSquared();

	Vector3D normalize();

	bool equals(Vector3D other);

	void toString();


};

#endif /* VECTOR3D_H_ */
