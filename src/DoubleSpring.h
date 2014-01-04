#ifndef DOUBLESPRING_H_
#define DOUBLESPRING_H_

#include <iostream>

#include "Sphere.h"
#include "Renderable.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"

/**
 * Represents a system of spring-spherespring-spere
 */
class DoubleSpring : public Renderable{

public:
	/**
	 * Constructs a spring-mass-spring-mass system
	 */
	DoubleSpring();
	~DoubleSpring(void);

	/**
	 * Render
	 */
	void draw();

	/**
	 * Update state based on physics laws
	 */
	void update();

	/**
	 *Gets sphere1 reference
	 */
	Sphere &getSphereOne();

	/**
	 *Gets sphere2 reference
	*/
	Sphere &getSphereTwo();

private:

	Sphere sphere1, sphereTwo;

	/**
	 * Anchor position
	 */
	Vector3 anchor;

	/**
	 * Rest length, stretch, spring k and dumping factor b
	 */
	float restLength1, restLength2;
	float stretch1, stretch2;
	float k1, k2;
	float b1, b2;

	/**
	 * Used to generate random numbers between [min-max]
	 *
	 * @param (min, max)
	 */
	float randMM(float min, float max);
	
};

#endif

