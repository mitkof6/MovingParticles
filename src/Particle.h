#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Renderable.h"
#include "Vector3D.h"

#include "Constants.h"

class Particle :public Renderable{

public:
	Particle(){};
	Particle(
		float r, float g, float b,
		float px, float py, float pz,
		float vx, float vy, float vz,
		float rad, float m);
	~Particle();

	bool operator==(Particle &p);
	float getRadius();

	float getMass();

	Vector3D getPosition();
	Vector3D getVelocity();

	void draw();
	void update();

	void collisionHandler(Vector3D wallDir);
	void collisionHandler(Particle p);

	void setCollision(bool flag);
	bool getCollision();
private:
	float radius, mass;
	Vector3D position, velocity;
	bool collision;
};

#endif