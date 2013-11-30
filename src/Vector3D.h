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

	Vector3D operator +(const Vector3D &other) const;
	Vector3D operator -(const Vector3D &other) const;
	Vector3D operator *(float c) const;
	Vector3D operator /(float c) const;

	float dot(const Vector3D &other) const;
	Vector3D cross(const Vector3D &other) const;

	float magnitude() const;
	float magnitudeSquared() const;

	Vector3D normalize() const;

	bool equals(const Vector3D &other) const;

	void toString() const;


};

#endif /* VECTOR3D_H_ */
