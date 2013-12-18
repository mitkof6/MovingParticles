#include "Molecule.h"


Molecule::Molecule(int n){

	//center
	center = Vector3( 
		randMM(MIN_X+2*MOL_RADIUS, MAX_X-2*MOL_RADIUS),
		randMM(MIN_Y+2*MOL_RADIUS, MAX_Y-2*MOL_RADIUS),
		randMM(MIN_Z+2*MOL_RADIUS, MAX_Z-2*MOL_RADIUS));
	
	float m = randMM(MOL_MASS_MIN, MOL_MASS_MAX);
	
	for(int i = 0;i<n;i++){
		if(i==0){
			displacement.push_back(center);
		}else if(i<5){
			displacement.push_back(
				center+Vector3(
				2*MOL_RADIUS*sin((i-1)*MOL_TH*PI/180.0),
				2*MOL_RADIUS*cos((i-1)*MOL_TH*PI/180.0),
				0));

		}else{
			displacement.push_back(
				center+Vector3(
				0,
				2*MOL_RADIUS*sin((i-5)*2*MOL_TH*PI/180.0),
				2*MOL_RADIUS*cos((i-5)*2*MOL_TH*PI/180.0)));
		}

		mass.push_back(m);
		radius.push_back(MOL_RADIUS);

		//color
		color.push_back(
			Vector3(randMM(0, 1), randMM(0, 1), randMM(0, 1)));
	}

	
	totalMass = 0.0f;
	center = Vector3(0, 0, 0);

	for(unsigned i = 0;i<displacement.size();i++){

		//center
		totalMass += mass[i];
		center = center + displacement[i]*mass[i];
	}
	center = center/totalMass;

	//correct relative displacement
	for(unsigned i = 0;i<displacement.size();i++){
		Vector3 newD = displacement[i] - center;
		displacement[i] = newD;
	}

	//define max radius
	maxRadius = 0.0f;
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

	//angular velocity and orientation
	R = Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	angularVelocity = Vector3(
		0.0f,
		0.0f,
		1.0f);

	//calculate total inertia
	float Ixx = 0.0f, Ixy = 0.0f, Ixz = 0.0f;
	float Iyx = 0.0f, Iyy = 0.0f, Iyz = 0.0f;
	float Izx = 00.f, Izy = 0.0f, Izz = 0.0f;
	
	if(MAX_MOL == 5){
		Ixx = 3*(2.0f/5*mass[0]*radius[0]*radius[0])+
			2*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
		Iyy = 3*(2.0f/5*mass[0]*radius[0]*radius[0])+
			2*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
		Izz = 2.0f/5*mass[0]*radius[0]*radius[0]+
			4*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
	}else if(MAX_MOL==7){
		Ixx = 3*(2.0f/5*mass[0]*radius[0]*radius[0])+
			4*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
		Iyy = 3*(2.0f/5*mass[0]*radius[0]*radius[0])+
			4*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
		Izz = 3*(2.0f/5*mass[0]*radius[0]*radius[0])+
			4*(2.0f/5*mass[0]*radius[0]*radius[0]+mass[0]*(2*radius[0])*(2*radius[0]));
	}
		
	inertia = Matrix3(
		Ixx, Ixy, Ixz,
		Iyx, Iyy, Iyz,
		Izx, Izy, Izz);

	inertiaInv = inertia.invert();


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

			//glutWireSphere(radius[i], SLICES, STACKS);
			glutSolidSphere(radius[i], SLICES, STACKS);
		glPopMatrix();
	}
	
	/*
	glMultMatrixf(R.toGLMatrix4());
	

	for(unsigned i = 0;i<displacement.size();i++){	
			
		
		glPushMatrix();
			glTranslatef(dis[i].x, dis[i].y, dis[i].z);

			glColor3f(color[i].x, color[i].y, color[i].z);

			glutSolidSphere(radius[i], SLICES, STACKS);
			
		glPopMatrix();
	}
	*/
	//glutWireSphere(maxRadius, SLICES, STACKS);

	glPopMatrix();
}

void Molecule::update(){
	center = center + linearVelocity*dt;
	
	updateRotationMatrix();
}

Vector3 &Molecule::getCenter(){
	return center;
}

void Molecule::setCenter(Vector3 c){
	center = c;
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

Matrix3 Molecule::getInertiaInv(){
	return inertiaInv;
}

float Molecule::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}

float Molecule::impulseMagnitude(
	Vector3 vA, Vector3 wA, Vector3 rA, Matrix3 iInvA, float mA,
	Vector3 vB, Vector3 wB, Vector3 rB, Matrix3 iInvB, float mB,
	Vector3 n){

	float j = 
		(-2*(vA+wA.cross(rA)-vB-wB.cross(rB)).dot(n))/
		(((iInvA*(rA.cross(n))).cross(rA)+(iInvB*(rB.cross(n))).cross(rB)).dot(n) +1/mA+1/mB);


	return j;
}

float Molecule::impulseMagnitude(
	Vector3 vA, Vector3 wA, Vector3 rA, Matrix3 iInvA, float mA,
	Vector3 n){

	
	float j = 
		(-2*(vA+wA.cross(rA)).dot(n))/
		(((iInvA*(rA.cross(n))).cross(rA)).dot(n) +1/mA);

	return j;
}

void Molecule::collisionHandler(Molecule &m, Vector3 cp, Vector3 cn){
	//cn = cn*(-1);
	Vector3 rA = cp - m.getCenter();
	Matrix3 iInvA = m.getInertiaInv();
	float mA = m.getTotalMass();

	float j = impulseMagnitude(
		m.getLinearVelocity(), m.getAngularVelocity(), rA, iInvA, mA,
		cn); 
	
	Vector3 J = j*cn;
	//std::cout<<"J "<<J<<std::endl;
	//std::cout<<"Total before: "<<m.getLinearVelocity().length()+m.getAngularVelocity().length()<<std::endl;

	m.setLinearVelocity(J/mA+m.getLinearVelocity());
	
	m.setAngularVelocity(iInvA*(rA.cross(J))+m.getAngularVelocity()*0.95);

	//std::cout<<"Total after: "<<m.getLinearVelocity().length()+m.getAngularVelocity().length()<<std::endl;

}

void Molecule::collisionHandler(Molecule &p, Molecule &q, Vector3 cp, Vector3 cn){
	Vector3 rA = cp - p.getCenter();
	Matrix3 iInvA = p.getInertiaInv();
	float mA = p.getTotalMass();

	Vector3 rB = cp - q.getCenter();
	Matrix3 iInvB = q.getInertiaInv();
	float mB = q.getTotalMass();

	float j = impulseMagnitude(
		p.getLinearVelocity(), p.getAngularVelocity(), rA, iInvA, mA,
		q.getLinearVelocity(), q.getAngularVelocity(), rB, iInvB, mB,
		cn); 
	
	Vector3 J = j*cn;
	
	p.setLinearVelocity(J/mA+p.getLinearVelocity());
	p.setAngularVelocity((iInvA*(rA.cross(J))+p.getAngularVelocity())*0.90);

	q.setLinearVelocity(-J/mB+q.getLinearVelocity());
	q.setAngularVelocity((iInvB*(rB.cross(-J))+p.getAngularVelocity())*0.90);
}

void Molecule::updateRotationMatrix(){
	//Quaternion q = Quaternion(angularVelocity.normalize(), 1.0f);
	//q.rotate(dt*angularVelocity.length());
	Quaternion q = Quaternion();
	q.scaledAxis(angularVelocity*dt);
	R =R*q.rotationMatrix();
	

	//update displacement
	for(unsigned i = 1;i<displacement.size();i++){

		displacement[i] = q.rotatedVector(displacement[i]);
		//displacement[i] = R*displacement[i];
	}

	//update inertia tensor
	inertia = R*inertia*R.transpose();
	inertiaInv = R*inertiaInv*R.transpose();


}


float Molecule::getTotalMass(){
	return totalMass;
}

Vector3 Molecule::getLinearVelocity(){
	return linearVelocity;
}

void Molecule::setLinearVelocity(Vector3 v){
	linearVelocity = v;
}

Vector3 Molecule::getAngularVelocity(){
	return angularVelocity;
}

void Molecule::setAngularVelocity(Vector3 w){
	angularVelocity = w;
}

void Molecule::setColor(int i, float r, float g, float b){
	color[i] = Vector3(r, g, b);
}

