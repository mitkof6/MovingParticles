#ifndef SPHERE_H_
#define SPHERE_H_

#include "Renderable.h"
#include "RigidBody.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"

/**
 * Representation of sphere (geometry and physics)
 */
class Sphere : public Renderable, public RigidBody{

public:
	/**
	 * Default constructor (does nothing)
	 */
	Sphere(){};

	/**
	 * Constructor
	 *
	 * @param (color(red, green, blue), position(x, y, z),
	 * 		   velocity(x, y, z), radius, mass)
	 */
	Sphere(
		float r, float g, float b,
		float px, float py, float pz,
		float vx, float vy, float vz,
		float rad, float m);
	~Sphere();

	/**
	 * Sets Material
	 *
	 * @param (ambient, diffuse, secular, shininess)
	 */
	void setMatirial(
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw,
		float sh);


	/**
	 * Checks of equals (sampe object in memory)
	 */
	bool operator==(Sphere &p);

	float getRadius();

	/**
	 * Render sphere
	 */
	void draw();

	/**
	 * Update position, velocity
	 */
	void update();

	/**
	 * Handles sphere-wall collision by reflection
	 *
	 * @param (wall normal (must be normalized))
	 */
	void collisionHandler(Vector3 dir);

	/**
	 * Handles Spheres collision
	 *
	 * @param (other sphere, collision mode)
	 */
	void collisionHandler(Sphere &p, bool collisionMode);

private:
	float radius;

	float red, green, blue;

	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	float shininess;

};

#endif
