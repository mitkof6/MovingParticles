#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Renderable.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"

class Particle :public Renderable{

public:
	Particle(){};
	Particle(
		float r, float g, float b,
		float px, float py, float pz,
		float vx, float vy, float vz,
		float rad, float m);
	~Particle();

	void setMatirial(
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw,
		float sh);


	bool operator==(Particle &p);

	float getRadius();

	float getMass();

	Vector3 &getPosition();
	void setPosition(Vector3 p);

	Vector3 &getVelocity();
	void setVelocity(Vector3 v);

	void draw();
	void update();

	void collisionHandler(Vector3 dir);
	void collisionHandler(Particle &p);

private:
	float radius, mass;
	Vector3 position, velocity;

	float red, green, blue;

	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	float shininess;

};

#endif