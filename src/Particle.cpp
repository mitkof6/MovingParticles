#include "Particle.h"
#include "GL\glut.h"

Particle::Particle(float r, float g, float b,
		float px, float py, float pz,
		float vx, float vy, float vz,
		float rad, float m) : Renderable(r, g, b){
	radius = rad;
	mass = m;
	position = Vector3D(px, py, pz);
	velocity = Vector3D(vx, vy, vz);

}


Particle::~Particle(){

}

float Particle::getRadius(){
	return radius;
}

float Particle::getMass(){
	return mass;
}

Vector3D Particle::getPosition(){
	return position;
}

Vector3D Particle::getVelocity(){
	return velocity;
}

void Particle::draw(){
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glPushMatrix();
	

	glColor3f(red, green, blue);

	glTranslatef(position.x, position.y, position.z);

	glutSolidSphere(radius, SLICES, STACKS);


	glPopMatrix();
}

void Particle::update(){

	position = position + velocity*dt;

}


