#ifndef DOUBLESPRING_H_
#define DOUBLESPRING_H_

#include <iostream>

#include "Particle.h"
#include "Renderable.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"

class DoubleSpring : public Renderable{

public:
	DoubleSpring();
	~DoubleSpring(void);

	void draw();
	void update();

private:
	Particle p1, p2;
	Vector3 anchor;

	float restLength1, restLength2;
	float stretch1, stretch2;
	float k1, k2;
	float b1, b2;

	float randMM(float min, float max);
};

#endif

