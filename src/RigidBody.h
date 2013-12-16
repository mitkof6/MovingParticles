#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "Renderable.h"
#include "Math\Matrices.h"
#include "Math\Vectors.h"


class RigidBody : public Renderable{

public:
	Vector3 x, v, omega;
	Matrix3 inertia, inertiaInv;
	Matrix3 R;
	float mass;

	RigidBody(void);
	~RigidBody(void);

};

#endif
