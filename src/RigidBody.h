#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Math/Matrices.h"
#include "Math/Vectors.h"


class RigidBody{

public:

	RigidBody(void);
	~RigidBody(void);

	Vector3 &getMassCenter();
	void setMassCenter(Vector3 c);


	Vector3 getLinearVelocity() const;
	void setLinearVelocity(Vector3 vv);

	Vector3 getAngularVelocity() const;
	void setAngularVelocity(Vector3 w);

	float getMass() const;

	Matrix3 getInertia() const;
	Matrix3 getInertiaInv() const;

	Matrix3 getOrientation() const;

protected:
	Vector3 x, v, omega;
	Matrix3 inertia, inertiaInv;
	Matrix3 orientation;
	float mass;
};

#endif
