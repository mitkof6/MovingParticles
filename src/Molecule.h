#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <iostream>
#include <vector>
#include <cmath>

#include "Renderable.h"
#include "Constants.h"
#include "Math/Vectors.h"
#include "Math/Matrices.h"
#include "Math/Quaternion.h"

#include "GL/glut.h"

#define PI 3.14

using namespace std;

class Molecule : public Renderable{

public:
	Molecule(int n);
	~Molecule(void);

	void draw();
	void update();

	Vector3 &getCenter();
	void setCenter(Vector3 c);

	float getTotalMass();

	Vector3 getAngularVelocity();
	void setAngularVelocity(Vector3 w);

	Vector3 getLinearVelocity();
	void setLinearVelocity(Vector3 v);

	float getMaxRadius();
	int getMoleculeCount();

	Matrix3 getInertiaInv();

	Vector3 getDisplacement(int i);
	float getRadius(int i);

	void setColor(int i, float r, float g, float b);

	void collisionHandler(Molecule &m, Vector3 cp, Vector3 cn);
	void collisionHandler(Molecule &p, Molecule &q, Vector3 cp, Vector3 cn);

private:
	vector<float> radius, mass;
	vector<Vector3> displacement, color;
	Vector3 center;
	Vector3 linearVelocity;

	Vector3 angularVelocity;

	float maxRadius;
	Matrix3 inertia, inertiaInv;
	Matrix3 R;
	float totalMass;

	float randMM(float min, float max);

	float impulseMagnitude(
		Vector3 vA, Vector3 wA, Vector3 rA, Matrix3 iInvA, float mA,
		Vector3 vB, Vector3 wB, Vector3 rB, Matrix3 iInvB, float mB,
		Vector3 n);

	float impulseMagnitude(
		Vector3 vA, Vector3 wA, Vector3 rA, Matrix3 iInvA, float mA,
		Vector3 n);

	void updateRotationMatrix();
};

#endif
