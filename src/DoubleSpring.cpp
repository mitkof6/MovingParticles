#include "DoubleSpring.h"


DoubleSpring::DoubleSpring(){

	restLength1 = restLength2 = 
		randMM(MIN_REST_LENGTH, MAX_REST_LENGTH);

	float mass = randMM(MASS_MIN, MASS_MAX);
	float radius = mass/(MASS_MAX-MASS_MIN);

	stretch1 = stretch2 = 0;

	k1 = k2 = randMM(MIN_SPRING_K, MAX_SPRING_K);
	b1 = b2 = randMM(MIN_SPRING_B, MAX_SPRING_B);

	//anchor
	anchor = Vector3(
		randMM(MIN_X+radius, MAX_X-radius),
		BOX_SIZE/2,
		randMM(MIN_Z+radius, MAX_Z-radius));

	//particles
	p1 = Particle(
		randMM(0, 1), randMM(0, 1), randMM(0, 1),
		anchor.x, anchor.y-restLength1, anchor.z,
		randMM(MIN_VX, MAX_VX),randMM(MIN_VY, MAX_VY), randMM(MIN_VZ, MAX_VZ),
		radius,
		mass);

	p2 =  Particle(
		randMM(0, 1), randMM(0, 1), randMM(0, 1),
		p1.getMassCenter().x, 
		p1.getMassCenter().y-restLength2,
		p1.getMassCenter().z,
		randMM(MIN_VX, MAX_VX),randMM(MIN_VY, MAX_VY), randMM(MIN_VZ, MAX_VZ),
		radius,
		mass);

	//matirials
	p1.setMatirial(
			randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
			randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
			randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
			randMM(SH_MIN, SH_MAX));
	p2.setMatirial(
			randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
			randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
			randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
			randMM(SH_MIN, SH_MAX));

	//force
	p1.clearForce();
	p2.clearForce();
}


DoubleSpring::~DoubleSpring(void){
	
		
}

void DoubleSpring::draw(){
	
	glPushMatrix();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(anchor.x, anchor.y, anchor.z);
		glVertex3f(p1.getMassCenter().x, p1.getMassCenter().y, p1.getMassCenter().z);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(p1.getMassCenter().x, p1.getMassCenter().y, p1.getMassCenter().z);
		glVertex3f(p2.getMassCenter().x, p2.getMassCenter().y, p2.getMassCenter().z);
	glEnd();

	p1.draw();
	p2.draw();

	glPopMatrix();
}

void DoubleSpring::update(){
	
	//aplay gravity
	p1.applayForce(Vector3(0, -p1.getMass()*G, 0));
	p2.applayForce(Vector3(0, -p2.getMass()*G, 0));

	//p1
	Vector3 pos1 = p1.getMassCenter();
	Vector3 v1 = p1.getLinearVelocity();

	float L1 = (pos1-anchor).length();
	stretch1 = L1 - restLength1;

	//p2
	Vector3 pos2 = p2.getMassCenter();
	Vector3 v2 = p2.getLinearVelocity();

	float L2 = (pos2-pos1).length();
	stretch2 = L2 - restLength2;
	

	//forces

	Vector3 dF1 = Vector3(
		-k1*stretch1*(pos1.x-anchor.x)/L1 - b1*v1.x + k2*stretch2*(pos2.x-pos1.x)/L1,
		-k1*stretch1*(pos1.y-anchor.y)/L1 - b1*v1.y + k2*stretch2*(pos2.y-pos1.y)/L1,
		-k1*stretch1*(pos1.z-anchor.z)/L1 - b1*v1.z + k2*stretch2*(pos2.z-pos1.z)/L1);
	p1.applayForce(dF1);

	Vector3 dF2 = Vector3(
		-k2*stretch2*(pos2.x-pos1.x)/L2 - b2*v2.x,
		-k2*stretch2*(pos2.y-pos1.y)/L2 - b2*v2.y,
		-k2*stretch2*(pos2.z-pos1.z)/L2 - b2*v2.z);
	p2.applayForce(dF2);

	
	//update p1
	Vector3 a1 = p1.getTotalForce()/p1.getMass();
	p1.setLinearVelocity(
		p1.getLinearVelocity()+a1*dt);
	p1.update();

	//update p2
	Vector3 a2 = p2.getTotalForce()/p2.getMass();
	p2.setLinearVelocity(
		p2.getLinearVelocity()+a2*dt);
	p2.update();

	//clear
	p1.clearForce();
	p2.clearForce();
}

Particle &DoubleSpring::getP1(){
	return p1;
}

Particle &DoubleSpring::getP2(){
	return p2;
}

float DoubleSpring::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}
