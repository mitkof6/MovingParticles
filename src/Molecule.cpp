#include "Molecule.h"


Molecule::Molecule(int n){

	for(int i = 0;i<n;i++){
		if(i==0){
			displacement.push_back(Vector3D(
				randMM(MIN_X+2*MAX_M/(MAX_M-MIN_M), MAX_X-2*MAX_M/(MAX_M-MIN_M)),
				randMM(MIN_Y+2*MAX_M/(MAX_M-MIN_M), MAX_Y-2*MAX_M/(MAX_M-MIN_M)),
				randMM(MIN_Z+2*MAX_M/(MAX_M-MIN_M), MAX_Z-2*MAX_M/(MAX_M-MIN_M))));

			mass.push_back(randMM(MIN_M, MAX_M));

			radius.push_back(mass[i]/(MAX_M-MIN_M));
		}else{
			displacement.push_back(displacement[0]+Vector3D(
				radius[0]*sin((i-1)*MOL_TH*PI/180.0),radius[0]*cos((i-1)*MOL_TH*PI/180.0), 0));

			mass.push_back(randMM(MIN_M, MAX_M));

			radius.push_back(mass[i]/(MAX_M-MIN_M));
		}
	}

	//center
	massCenter = Vector3D(0, 0, 0);
	totalMass = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		//color
		color.push_back(Vector3D(randMM(0, 1), randMM(0, 1), randMM(0, 1)));

		//center
		totalMass += mass[i];
		massCenter = massCenter + displacement[i]*mass[i];
	}
	massCenter = massCenter/totalMass;

	//correct relative displacement
	for(unsigned i = 0;i<displacement.size();i++){
		Vector3D newD = displacement[i] - massCenter;
		displacement[i] = newD;
	}

	//define max radius
	maxRadius = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		float temp = (displacement[i]).magnitude()+radius[i];

		if(temp>maxRadius){
			maxRadius = temp;
		}
	}

	//velocity
	velocity = Vector3D(
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX),
		randMM(MIN_VX, MAX_VX));

	//angular velosity
	rotationalVelocity = Vector3D(0, 0, 0);
	rotationAxis = Vector3D(0, 0, 0);

	//calculate total inertia
	//Σ(mi*r^2+mi*di^2)
	totalInertia = 0;
	for(unsigned i = 0;i<displacement.size();i++){
		totalInertia += 2/3*mass[i]*radius[i]*radius[i]+
			mass[i]*displacement[i].magnitudeSquared();
	}
	
}


Molecule::~Molecule(void){

}

void Molecule::draw(){

	glPushMatrix();

	glTranslatef(massCenter.x, massCenter.y, massCenter.z);
	glRotatef(th, 
		rotationAxis.x, rotationAxis.y, rotationAxis.z);
	

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
	massCenter = massCenter + velocity*dt;
	//anglularVelocity = anglularVelocity + Vector3D(10, 0, 0);//TODO
}

Vector3D Molecule::getMassCenter(){
	return massCenter;
}

void Molecule::setMassCenter(Vector3D c){
	massCenter = c;
}


float Molecule::getMaxRadius(){
	return maxRadius;
}

int Molecule::getMoleculeCount(){
	return displacement.size();
}

Vector3D Molecule::getDisplacement(int i){
	return displacement[i];
}

float Molecule::getRadius(int i){
	return radius[i];
}

float Molecule::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}

void Molecule::collisionHandler(Vector3D dir){
	//reflect velocity
	velocity = velocity - dir*velocity.dot(dir)*2;
}

void Molecule::collisionHandler(Molecule &q){

	Vector3D displacement = massCenter-q.getMassCenter();
	Vector3D n = displacement.normalize();

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

void Molecule::setRotationalVelocity(Vector3D a){
	rotationalVelocity = rotationalVelocity + a;
}

void Molecule::setRotationAxis(Vector3D rot){
	rotationAxis = rot;
}

void Molecule::applyForce(Molecule &m, Vector3D &cp, Vector3D &cn){
	Vector3D f = cn*m.getTotalMass();
	
	Vector3D t = cp.cross(f);

	Vector3D a = t/m.getTotalInertia();

	m.setRotationAxis((((cp-m.getMassCenter()).cross(cn)+rotationAxis)/2).normalize());
	m.setRotationalVelocity(Vector3D(0, 0, 0));
	
}
