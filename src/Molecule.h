#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <iostream>
#include <vector>
#include <cmath>

#include "Renderable.h"
#include "Constants.h"
#include "RigidBody.h"
#include "Math/Vectors.h"
#include "Math/Matrices.h"
#include "Math/Quaternion.h"

#include "GL/glut.h"

#define PI 3.14

using namespace std;

class Molecule : public Renderable, public RigidBody{

public:
	Molecule(int n);
	~Molecule(void);

	void draw();
	void update();

	float getMaxRadius();
	int getMoleculeCount();

	Vector3 getDisplacement(int i);
	float getRadius(int i);

	void setColor(int i, float r, float g, float b);

	void collisionHandler(Molecule &m, Vector3 cp, Vector3 cn);
	void collisionHandler(Molecule &p, Molecule &q, Vector3 cp, Vector3 cn);

private:
	vector<float> radius, masses;
	vector<Vector3> displacement, dis, color;

	float maxRadius;

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
