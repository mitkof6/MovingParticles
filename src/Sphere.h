#ifndef SPHERE_H_
#define SPHERE_H_

#include "Renderable.h"
#include "RigidBody.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"


class Sphere : public Renderable, public RigidBody{

public:
	Sphere(){};
	Sphere(
		float r, float g, float b,
		float px, float py, float pz,
		float vx, float vy, float vz,
		float rad, float m);
	~Sphere();

	void setMatirial(
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw,
		float sh);


	bool operator==(Sphere &p);

	float getRadius();

	void draw();
	void update();

	void collisionHandler(Vector3 dir);
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
