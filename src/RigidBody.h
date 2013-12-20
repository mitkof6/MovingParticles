#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Math/Matrices.h"
#include "Math/Vectors.h"


class RigidBody{

public:

	RigidBody(void);
	virtual ~RigidBody(void);

	virtual Vector3 &getMassCenter();
	virtual void setMassCenter(Vector3 c);


	virtual Vector3 getLinearVelocity() const;
	virtual void setLinearVelocity(Vector3 vv);

	virtual Vector3 getAngularVelocity() const;
	virtual void setAngularVelocity(Vector3 w);

	virtual float getMass() const;

	virtual Matrix3 getInertia() const;
	virtual Matrix3 getInertiaInv() const;

	virtual Matrix3 getOrientation() const;

	virtual void applayForce(Vector3 f);
	virtual void clearForce();
	virtual Vector3 getTotalForce() const;

protected:
	Vector3 x, v, omega;
	Matrix3 inertia, inertiaInv;
	Matrix3 orientation;
	float mass;

	Vector3 totalForce;
};

#endif
