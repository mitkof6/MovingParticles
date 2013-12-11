#include "Molecule.h"


Molecule::Molecule(int n){

	for(int i = 0;i<n;i++){
		if(i==0){
			displacement.push_back(Vector3(
				randMM(MIN_X+2*MAX_M/(MAX_M-MIN_M), MAX_X-2*MAX_M/(MAX_M-MIN_M)),
				randMM(MIN_Y+2*MAX_M/(MAX_M-MIN_M), MAX_Y-2*MAX_M/(MAX_M-MIN_M)),
				randMM(MIN_Z+2*MAX_M/(MAX_M-MIN_M), MAX_Z-2*MAX_M/(MAX_M-MIN_M))));

			mass.push_back(randMM(MIN_M, MAX_M));

			radius.push_back(mass[i]/(MAX_M-MIN_M));
		}else{
			displacement.push_back(displacement[0]+Vector3(
				radius[0]*sin((i-1)*MOL_TH*PI/180.0),radius[0]*cos((i-1)*MOL_TH*PI/180.0), 0));

			mass.push_back(randMM(MIN_M, MAX_M));

			radius.push_back(mass[i]/(MAX_M-MIN_M));
		}
	}

	//center
	massCenter = Vector3(0, 0, 0);
	totalMass = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		//color
		color.push_back(Vector3(randMM(0, 1), randMM(0, 1), randMM(0, 1)));

		//center
		totalMass += mass[i];
		massCenter = massCenter + displacement[i]*mass[i];
	}
	massCenter = massCenter/totalMass;

	//correct relative displacement
	for(unsigned i = 0;i<displacement.size();i++){
		Vector3 newD = displacement[i] - massCenter;
		displacement[i] = newD;
	}

	//define max radius
	maxRadius = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		float temp = (displacement[i]).length()+radius[i];

		if(temp>maxRadius){
			maxRadius = temp;
		}
	}

	//velocity
	linearVelocity = Vector3(
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX));

	//angular velosity and orientation
	orientation = Vector3(
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX));
	angularVelocity = Vector3(
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX));

	//calculate total inertia
	//Σ(mi*r^2+mi*di^2)
	totalInertia = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		totalInertia += 2/3*mass[i]*radius[i]*radius[i]+
			mass[i]*displacement[i].lengthSq();
	}
	
}


Molecule::~Molecule(void){

}

void Molecule::draw(){

	glPushMatrix();

	glTranslatef(massCenter.x, massCenter.y, massCenter.z);
	glRotatef(orientation.length(), 
		orientation.x, orientation.y, orientation.z);
	

	for(unsigned i = 0;i<displacement.size();i++){
		glPushMatrix();
			glTranslatef(displacement[i].x, displacement[i].y, displacement[i].z);

			glColor3f(color[i].x, color[i].y, color[i].z);

			glutSolidSphere(radius[i], SLICES, STACKS);
			
		glPopMatrix();
	}

	glutWireSphere(maxRadius, SLICES, STACKS);

	glPopMatrix();

}

void Molecule::update(){
	massCenter = massCenter + linearVelocity*dt;
	orientation = orientation + angularVelocity*dt;
}

Vector3 &Molecule::getMassCenter(){
	return massCenter;
}

void Molecule::setMassCenter(Vector3 c){
	massCenter = c;
}

float Molecule::getMaxRadius(){
	return maxRadius;
}

int Molecule::getMoleculeCount(){
	return displacement.size();
}

Vector3 Molecule::getDisplacement(int i){
	return displacement[i];
}

float Molecule::getRadius(int i){
	return radius[i];
}

float Molecule::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}

void Molecule::collisionHandler(Vector3 dir){
	//reflect velocity
	linearVelocity = linearVelocity - dir*linearVelocity.dot(dir)*2;
}

void Molecule::collisionHandler(Molecule &q){

	Vector3 displacement = massCenter-q.getMassCenter();
	Vector3 n = displacement.normalize();

	//if simulation is not real mode (velocity change in direction)
	if(!BALL_COLLISION_REAL_MODE){
				
		collisionHandler(n);
		q.collisionHandler(n*(1));	  //TODO
		
		return;
	}

	//TODO real collision
}

float Molecule::getTotalMass(){
	return totalMass;
}

float Molecule::getTotalInertia(){
	return totalInertia;
}

Vector3 Molecule::getAngularVelocity(){
	return angularVelocity;
}

void Molecule::setAngularVelocity(Vector3 a){
	angularVelocity = a;
}

void Molecule::applyForce(Molecule &m, Vector3 &cp, Vector3 &cn){
	Vector3 f = cn*m.getTotalMass();
	
	Vector3 t = cp.cross(f);

	Vector3 a = t/m.getTotalInertia();

	//m.setRotationAxis((((cp-m.getMassCenter()).cross(cn)+rotationAxis)/2).normalize());
	//m.setRotationalVelocity(Vector3(0, 0, 0));
	
}
