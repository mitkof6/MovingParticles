#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <iostream>
#include <vector>
#include <cmath>

#include "Renderable.h"
#include "Constants.h"
#include "Math/Vectors.h"

#include "GL/glut.h"

#define PI 3.14

using namespace std;

class Molecule : public Renderable{

public:
	Molecule(int n);
	~Molecule(void);

	void draw();
	void update();

	Vector3 &getMassCenter();
	void setMassCenter(Vector3 c);

	float getTotalMass();
	float getTotalInertia();

	Vector3 getAngularVelocity();
	void setAngularVelocity(Vector3 a);

	Vector3 getLinearVelocity();
	void setLinearVelocity(Vector3 a);

	float getMaxRadius();
	int getMoleculeCount();

	Vector3 getDisplacement(int i);
	float getRadius(int i);

	void applyForce(Molecule &m, Vector3 &cp, Vector3 &cn);

	void collisionHandler(Vector3 dir);
	void collisionHandler(Molecule &q, bool collisionMode);

private:
	vector<float> radius, mass;
	vector<Vector3> displacement, color;
	Vector3 massCenter;
	Vector3 linearVelocity;

	Vector3 orientation;
	Vector3 angularVelocity;

	float maxRadius;
	float totalInertia;
	float totalMass;

	float randMM(float min, float max);

};

#endif
