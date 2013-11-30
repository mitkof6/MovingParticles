#include "Particle.h"
#include "GL/glut.h"

Particle::Particle(
	float r, float g, float b,
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

void Particle::setPosition(Vector3D p){
	position = p;
}

Vector3D Particle::getVelocity(){
	return velocity;
}

void Particle::setVelocity(Vector3D v){
	velocity = v;
}

void Particle::draw(){
	glPushMatrix();

		glColor3f(red, green, blue);

		glTranslatef(position.x, position.y, position.z);

		glutSolidSphere(radius, SLICES, STACKS);

	glPopMatrix();
}

void Particle::update(){
	position = position + velocity*dt;
}

/**
	@param dir must be normalized
*/
void Particle::collisionHandler(Vector3D dir){
	//reflect velocity
	velocity = velocity - dir*velocity.dot(dir)*2;
}

void Particle::collisionHandler(Particle &p){

	Vector3D displacement = position-p.getPosition();
	Vector3D n = displacement.normalize();
	float dr = (radius+p.getRadius()-displacement.magnitude())/2;

	//correction
	position = position+n*dr;
	displacement = position-p.getPosition();
	n = displacement.normalize();

	//if simulation is not real mode (velocity change in direction)
	if(!BALL_COLLISION_REAL_MODE){
		collisionHandler(n);
		p.collisionHandler(n*(-1));
		return;
	}

	//find orthonormals	 (n, t, o)
	Vector3D t(1, 0, 0);
	t = n.cross(t);

	//if t, n parallel
	if(t.magnitude()==0){
		Vector3D t(0, 1, 0);
		t = n.cross(t);
	}

	Vector3D o = n.cross(t);

	//v1 = v1*m11+v2*m21
	float m11 = (mass-p.getMass())/(mass+p.getMass());
	float m12 = 2*p.getMass()/(mass+p.getMass());

	float v1n = n.dot(velocity)*m11+n.dot(p.getVelocity())*m12;
	float v1t = t.dot(velocity)*m11+t.dot(p.getVelocity())*m12;
	float v1o = o.dot(velocity)*m11+o.dot(p.getVelocity())*m12;

	//v2 = v2*m21+v1*m22
	float m21 = (p.getMass()-mass)/(mass+p.getMass());
	float m22 = 2*mass/(mass+p.getMass());

	float v2n = n.dot(p.getVelocity())*m21+n.dot(velocity)*m22;
	float v2t = t.dot(p.getVelocity())*m21+t.dot(velocity)*m22;
	float v2o = o.dot(p.getVelocity())*m21+o.dot(velocity)*m22;

	//change velocity
	velocity = n*v1n+t*v1t+o*v1o;
	p.setVelocity(n*v2n+t*v2t+o*v2o);
}


