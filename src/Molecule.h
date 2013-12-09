#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <iostream>
#include <vector>
#include <cmath>

#include "Renderable.h"
#include "Constants.h"
#include "Vector3D.h"

#include "GL/glut.h"

#define PI 3.14

using namespace std;

class Molecule : public Renderable{

public:
	Molecule(int n);
	~Molecule(void);

	void draw();
	void update();

	Vector3D getMassCenter();
	void setMassCenter(Vector3D c);

	float getMaxRadius();
	int getMoleculeCount();

	Vector3D getDisplacement(int i);
	float getRadius(int i);

	float getTotalMass();
	float getTotalInertia();

	void setAngularVelocity(Vector3D a);
	void setRotationAxis(Vector3D rot);

	float randMM(float min, float max);

	void applyForce(Molecule &m, Vector3D &cp, Vector3D &cn);

	void collisionHandler(Vector3D dir);
	void collisionHandler(Molecule &q);

private:
	vector<float> radius, mass;
	vector<Vector3D> displacement, color;
	Vector3D massCenter;
	Vector3D velocity;
	Vector3D anglularVelocity;
	Vector3D rotationAxis;
	float maxRadius;
	float totalInertia;
	float totalMass;

};

#endif
