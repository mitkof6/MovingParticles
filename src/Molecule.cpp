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
	center = Vector3D(0, 0, 0);
	for(unsigned i = 0;i<displacement.size();i++){
		//color
		color.push_back(Vector3D(randMM(0, 1), randMM(0, 1), randMM(0, 1)));

		//center
		center = center + displacement[i];
	}
	center = center/displacement.size();

	//correct relative displacement
	for(unsigned i = 0;i<displacement.size();i++){
		Vector3D newD = displacement[i] - center;
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
}


Molecule::~Molecule(void){

}

void Molecule::draw(){

	glPushMatrix();

	glTranslatef(center.x, center.y, center.z);

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
	center = center + velocity*dt;
}

Vector3D Molecule::getCenter(){
	return center;
}

void Molecule::setCenter(Vector3D c){
	center = c;
}


float Molecule::getMaxRadius(){
	return maxRadius;
}

float Molecule::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}

void Molecule::collisionHandler(Vector3D dir){
	//reflect velocity
	velocity = velocity - dir*velocity.dot(dir)*2;
}
