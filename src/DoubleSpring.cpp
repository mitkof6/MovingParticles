#include "DoubleSpring.h"


DoubleSpring::DoubleSpring(){

	restLength1 = restLength2 = 
		randMM(MIN_REST_LENGTH, MAX_REST_LENGTH);

	float mass1 = randMM(MASS_MIN, MASS_MAX);
	float radius1 = mass1/(MASS_MAX-MASS_MIN);

	float mass2 = randMM(MASS_MIN, MASS_MAX);
	float radius2 = mass2/(MASS_MAX-MASS_MIN);

	stretch1 = stretch2 = 0;

	k1 = k2 = randMM(MIN_SPRING_K, MAX_SPRING_K);
	b1 = b2 = randMM(MIN_SPRING_B, MAX_SPRING_B);

	//anchor
	anchor = Vector3(
		randMM(MIN_X+radius1, MAX_X-radius1),
		BOX_SIZE/2,
		randMM(MIN_Z+radius1, MAX_Z-radius1));

	//particles
	sphere1 = Sphere(
		randMM(0, 1), randMM(0, 1), randMM(0, 1),
		anchor.x, anchor.y-restLength1, anchor.z,
		randMM(MIN_VX, MAX_VX),randMM(MIN_VY, MAX_VY), randMM(MIN_VZ, MAX_VZ),
		radius1,
		mass1);

	sphereTwo =  Sphere(
		randMM(0, 1), randMM(0, 1), randMM(0, 1),
		sphere1.getMassCenter().x, 
		sphere1.getMassCenter().y-restLength2,
		sphere1.getMassCenter().z,
		randMM(MIN_VX, MAX_VX),randMM(MIN_VY, MAX_VY), randMM(MIN_VZ, MAX_VZ),
		radius2,
		mass2);

	//Materials
	sphere1.setMatirial(
			randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
			randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
			randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
			randMM(SH_MIN, SH_MAX));
	sphereTwo.setMatirial(
			randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
			randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
			randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
			randMM(SH_MIN, SH_MAX));

	//force
	sphere1.clearForce();
	sphereTwo.clearForce();
}


DoubleSpring::~DoubleSpring(void){
	
		
}

void DoubleSpring::draw(){
	
	glPushMatrix();

	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
		glVertex3f(anchor.x, anchor.y, anchor.z);
		glVertex3f(sphere1.getMassCenter().x, sphere1.getMassCenter().y, sphere1.getMassCenter().z);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(sphere1.getMassCenter().x, sphere1.getMassCenter().y, sphere1.getMassCenter().z);
		glVertex3f(sphereTwo.getMassCenter().x, sphereTwo.getMassCenter().y, sphereTwo.getMassCenter().z);
	glEnd();

	sphere1.draw();
	sphereTwo.draw();

	glPopMatrix();
}

void DoubleSpring::update(){
	
	//apply gravity
	sphere1.applayForce(Vector3(0, -sphere1.getMass()*G, 0));
	sphereTwo.applayForce(Vector3(0, -sphereTwo.getMass()*G, 0));

	//sphere1
	Vector3 pos1 = sphere1.getMassCenter();
	Vector3 v1 = sphere1.getLinearVelocity();

	float L1 = (pos1-anchor).length();
	stretch1 = L1 - restLength1;

	//sphere2
	Vector3 pos2 = sphereTwo.getMassCenter();
	Vector3 v2 = sphereTwo.getLinearVelocity();

	float L2 = (pos2-pos1).length();
	stretch2 = L2 - restLength2;
	

	//forces
	Vector3 dF1 = Vector3(
		-k1*stretch1*(pos1.x-anchor.x)/L1 - b1*v1.x + k2*stretch2*(pos2.x-pos1.x)/L1,
		-k1*stretch1*(pos1.y-anchor.y)/L1 - b1*v1.y + k2*stretch2*(pos2.y-pos1.y)/L1,
		-k1*stretch1*(pos1.z-anchor.z)/L1 - b1*v1.z + k2*stretch2*(pos2.z-pos1.z)/L1);
	sphere1.applayForce(dF1);

	Vector3 dF2 = Vector3(
		-k2*stretch2*(pos2.x-pos1.x)/L2 - b2*v2.x,
		-k2*stretch2*(pos2.y-pos1.y)/L2 - b2*v2.y,
		-k2*stretch2*(pos2.z-pos1.z)/L2 - b2*v2.z);
	sphereTwo.applayForce(dF2);

	
	//update sphere1
	Vector3 a1 = sphere1.getTotalForce()/sphere1.getMass();
	sphere1.setLinearVelocity(
		sphere1.getLinearVelocity()+a1*dt);
	sphere1.update();

	//update sphere2
	Vector3 a2 = sphereTwo.getTotalForce()/sphereTwo.getMass();
	sphereTwo.setLinearVelocity(
		sphereTwo.getLinearVelocity()+a2*dt);
	sphereTwo.update();

	//clear forces
	sphere1.clearForce();
	sphereTwo.clearForce();
}

Sphere &DoubleSpring::getSphereOne(){
	return sphere1;
}

Sphere &DoubleSpring::getSphereTwo(){
	return sphereTwo;
}

float DoubleSpring::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}
