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

	float randMM(float min, float max);

	void collisionHandler(Vector3D dir);
	void collisionHandler(Molecule &q);

private:
	vector<float> radius, mass;
	vector<Vector3D> displacement, color;
	Vector3D massCenter;
	Vector3D velocity;
	Vector3D anglularVelocity;
	float maxRadius;
	float totalInertia;

};

#endif
