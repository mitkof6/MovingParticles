#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Math/Matrices.h"
#include "Math/Vectors.h"

/**
 * Defines common physics of rigid body.
 *
 * position of mass center
 * velocity
 * angular velocity
 * total mass
 * orientation
 * inertia (inverse)
 * active forces
 *
 */
class RigidBody{

public:

	RigidBody(void);
	virtual ~RigidBody(void);

	/**
	 * Getter and setter for mass center
	 */
	Vector3 &getMassCenter();
	void setMassCenter(Vector3 c);

	/**
	* Getter and setter for velocity
	*/
	Vector3 &getLinearVelocity();
	void setLinearVelocity(Vector3 vv);

	/**
	* Getter and setter for angular velocity
	*/
	Vector3 &getAngularVelocity();
	void setAngularVelocity(Vector3 w);

	/**
	 * Total mass getter
	 */
	float getMass() const;

	/**
	 * Inertia getters
	 */
	Matrix3 getInertia() const;
	Matrix3 getInertiaInv() const;

	/**
	 * Orientation of rigid body 3x3 matrix
	 */
	Matrix3 getOrientation() const;

	/**
	 * Adds a force to total body force
	 *
	 * @param (force)
	 */
	void applayForce(Vector3 f);

	/**
	 * Clears forces
	 */
	void clearForce();

	/**
	 * Gets total force
	 */
	Vector3 getTotalForce() const;

protected:
	Vector3 x, v, omega;
	Matrix3 inertia, inertiaInv;
	Matrix3 orientation;
	float mass;

	Vector3 totalForce;
};

#endif
