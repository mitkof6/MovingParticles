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

	collision = false;
}


Particle::~Particle(){

}

bool Particle::operator==(Particle &p){
	if(this==&p) return true;
	return false;
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

void Particle::setCollision(bool flag){
	collision = flag;
}

bool Particle::getCollision(){
	return collision;
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

void Particle::collisionHandler(Vector3D wallDir){
	Vector3D normWallDir = wallDir.normalize();

	velocity = velocity - normWallDir*velocity.dot(normWallDir)*2;
}

void Particle::collisionHandler(Particle p){
	velocity = 
		(velocity*(mass-p.getMass()) + p.getVelocity()*p.getMass()*2)/
		(mass+p.getMass());
	/*
	Vector3D dis = position-p.getPosition();
	Vector3D disn = dis.normalize();

	float amount = velocity.dot(disn);

	while( (position-p.getPosition()).magnitude() < radius+p.getRadius()){
		position = position + disn*amount*0.1;
	}
	 */

}


