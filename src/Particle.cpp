#include "Particle.h"

Particle::Particle(
	float r, float g, float b,
	float px, float py, float pz,
	float vx, float vy, float vz,
	float rad, float m){

	red = r;
	green = g;
	blue = b;

	radius = rad;
	mass = m;
	x = Vector3(px, py, pz);
	v = Vector3(vx, vy, vz);
}


Particle::~Particle(){

}

void Particle::setMatirial(
		float ax, float ay, float az, float aw,
		float dx, float dy, float dz, float dw,
		float sx, float sy, float sz, float sw,
		float sh){


	ambient[0] = ax;
	ambient[1] = ay;
	ambient[2] = az;
	ambient[3] = aw;

	diffuse[0] = dx;
	diffuse[1] = dy;
	diffuse[2] = dz;
	diffuse[3] = dw;

	specular[0] = sx;
	specular[1] = sy;
	specular[2] = sz;
	specular[3] = sw;

	shininess = sh;
}

bool Particle::operator==(Particle &p){
	if(this==&p) return true;
	return false;
}

float Particle::getRadius(){
	return radius;
}

void Particle::draw(){
	glPushMatrix();

		glColor3f(red, green, blue);

		//metirial
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

		glTranslatef(x.x, x.y, x.z);

		glutSolidSphere(radius, SLICES, STACKS);

	glPopMatrix();
}

void Particle::update(){
	x = x + v*dt;
}

void Particle::collisionHandler(Vector3 dir){
	//reflect velocity
	v = v - dir*v.dot(dir)*2;
	
}

void Particle::collisionHandler(Particle &p, bool collisionMode){
	
	Vector3 displacement = x-p.getMassCenter();
	Vector3 n = displacement.normalize();

	//if simulation is not real mode (velocity change in direction)
	if(!collisionMode){
				
		collisionHandler(n);
		p.collisionHandler(n*(-1));
		
		return;
	}

	//find orthonormals	 (n, t, o)
	Vector3 t(1, 0, 0);
	t = n.cross(t).normalize();

	//if t, n parallel
	if(t.length()==0){
		//std::cout<<"papalel\n";
		Vector3 t(0, 1, 0);
		t = n.cross(t).normalize();
	}

	Vector3 o = n.cross(t).normalize();

	//v1 = v1*m11+v2*m21
	float m11 = (mass-p.getMass())/(mass+p.getMass());
	float m12 = 2*p.getMass()/(mass+p.getMass());

	float v1n = n.dot(v)*m11+n.dot(p.getLinearVelocity())*m12;
	//float v1t = t.dot(velocity)*m11+t.dot(p.getVelocity())*m12;
	//float v1o = o.dot(velocity)*m11+o.dot(p.getVelocity())*m12;
	float v1t = t.dot(v);
	float v1o = o.dot(v);

	//v2 = v2*m21+v1*m22
	float m21 = (p.getMass()-mass)/(mass+p.getMass());
	float m22 = 2*mass/(mass+p.getMass());

	float v2n = n.dot(p.getLinearVelocity())*m21+n.dot(v)*m22;
	//float v2t = t.dot(p.getVelocity())*m21+t.dot(velocity)*m22;
	//float v2o = o.dot(p.getVelocity())*m21+o.dot(velocity)*m22;
	float v2t = t.dot(p.getLinearVelocity());
	float v2o = o.dot(p.getLinearVelocity());

	//change velocity
	v = n*v1n+t*v1t+o*v1o;
	p.setLinearVelocity(n*v2n+t*v2t+o*v2o);
}


