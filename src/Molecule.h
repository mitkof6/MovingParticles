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

private:
	vector<float> radius, masses;
	vector<Vector3> displacement, dis, color;

	float maxRadius;

	float randMM(float min, float max);

	void updateRotationMatrix();
};

#endif
