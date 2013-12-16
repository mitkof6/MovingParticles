#include "Molecule.h"

#include "glm.hpp"


Molecule::Molecule(int n){

	//center
	massCenter = Vector3( 
		randMM(MIN_X+2*MOL_RADIUS, MAX_X-2*MOL_RADIUS),
		randMM(MIN_Y+2*MOL_RADIUS, MAX_Y-2*MOL_RADIUS),
		randMM(MIN_Z+2*MOL_RADIUS, MAX_Z-2*MOL_RADIUS));
	
	float m = randMM(MOL_MASS_MIN, MOL_MASS_MAX);
	
	for(int i = 0;i<n;i++){
		if(i==0){
			displacement.push_back(massCenter);
		}else if(i<5){
			displacement.push_back(
				massCenter+Vector3(
				2*MOL_RADIUS*sin((i-1)*MOL_TH*PI/180.0),
				2*MOL_RADIUS*cos((i-1)*MOL_TH*PI/180.0),
				0));

		}else{
			displacement.push_back(
				massCenter+Vector3(
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
	massCenter = Vector3(0, 0, 0);
	for(unsigned i = 0;i<displacement.size();i++){

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

	//angular velosity and orientation
	R = Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);

	angularVelocity = Vector3(
		0.0f,
		10.0f,
		10.0f);

	//calculate total inertia
	float Ixx = 0.0f, Ixy = 0.0f, Ixz = 0.0f;
	float Iyx = 0.0f, Iyy = 0.0f, Iyz = 0.0f;
	float Izx = 00.f, Izy = 0.0f, Izz = 0.0f;
	for(unsigned i = 0;i<displacement.size();i++){
		Vector3 d = displacement[i];
		
		Ixx += mass[i]*(d.z*d.z+d.y*d.y);
		
		//Ixy += -2.0f/5*mass[i]*(d.x*d.y);
		//Ixz += -2.0f/5*mass[i]*(d.x*d.z);

		Iyy += mass[i]*(d.z*d.z+d.x*d.x);
		//Iyz += -2.0f/5*mass[i]*(d.y*d.z);

		Izz += mass[i]*(d.x*d.x+d.y*d.y);
	}
	//Iyx = Ixy;
	//Izx = Ixz;
	//Izy = Iyz;
	
	inertia = Matrix3(
		Ixx, Ixy, Ixz,
		Iyx, Iyy, Iyz,
		Izx, Izy, Izz);
	
	//std::cout<<inertia;
	inertiaInv = inertia.invert();

	//update R, I, Iinv
	//updateRotationMatrix();

}


Molecule::~Molecule(void){

}
Vector3 ccp(0, 0, 0);

void Molecule::draw(){

	glPushMatrix();

	glTranslatef(massCenter.x, massCenter.y, massCenter.z);
	//glRotatef(th.length(), 
		//th.x, th.y, th.z);
	glColor3f(1, 1, 1);
	glBegin(GL_LINE_LOOP);
		glVertex3f(0, 0, 0);
		glVertex3f(angularVelocity.x, angularVelocity.y, angularVelocity.z);
	glEnd();
	
	glMultMatrixf(R.toGLMatrix4());
	

	for(unsigned i = 0;i<displacement.size();i++){
		glPushMatrix();
			glTranslatef(displacement[i].x, displacement[i].y, displacement[i].z);

			glColor3f(color[i].x, color[i].y, color[i].z);

			glutSolidSphere(radius[i], SLICES, STACKS);
			
		glPopMatrix();
	}

	glutWireSphere(maxRadius, SLICES, STACKS);

	glPopMatrix();

	glPushMatrix();
	glTranslatef(ccp.x, ccp.y, ccp.z);
	glColor3f(1, 1, 1);
	glutWireSphere(0.5, SLICES, STACKS);

	glPopMatrix();
}

void Molecule::update(){
	massCenter = massCenter + linearVelocity*dt;
	
	updateRotationMatrix();
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
	//if((vA+wA.cross(rA)-vB-wB.cross(rB)).dot(n)<0.0f) return 0;
	float j = 
		(-2*(vA+wA.cross(rA)-vB-wB.cross(rB)).dot(n))/
		(((iInvA*(rA.cross(n))).cross(rA)+(iInvB*(rB.cross(n))).cross(rB)).dot(n) +1/mA+1/mB);

	//std::cout<<"Uref: "<<(vA+wA.cross(rA)-vB-wB.cross(rB)).dot(n)<<std::endl;
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
	Vector3 rA = cp - m.getMassCenter();
	Matrix3 iInvA = m.getInertiaInv();
	float mA = m.getTotalMass();

	float j = impulseMagnitude(
		m.getLinearVelocity(), m.getAngularVelocity(), rA, iInvA, mA,
		cn); 
	
	Vector3 J = j*cn;
	//std::cout<<"J "<<J<<std::endl;
	//std::cout<<"Linear before: "<<m.getLinearVelocity().length()<<std::endl;
	m.setLinearVelocity(J/mA+m.getLinearVelocity());
	//std::cout<<"Angular Before: "<<m.getAngularVelocity().length()<<"\n";
	m.setAngularVelocity(iInvA*(rA.cross(J))+m.getAngularVelocity());
	//std::cout<<"Angular After: "<<m.getAngularVelocity().length()<<"\n";
	//std::cout<<"Linear after: "<<m.getLinearVelocity().length()<<std::endl;;
	
	ccp = cp;
}

void Molecule::collisionHandler(Molecule &p, Molecule &q, Vector3 cp, Vector3 cn){
	Vector3 rA = cp - p.getMassCenter();
	Matrix3 iInvA = p.getInertiaInv();
	float mA = p.getTotalMass();

//	ccp = cp;

	Vector3 rB = cp - q.getMassCenter();
	Matrix3 iInvB = q.getInertiaInv();
	float mB = q.getTotalMass();

	float j = impulseMagnitude(
		p.getLinearVelocity(), p.getAngularVelocity(), rA, iInvA, mA,
		q.getLinearVelocity(), q.getAngularVelocity(), rB, iInvB, mB,
		cn); 
	
	Vector3 J = j*cn;
	
	p.setLinearVelocity(J/mA+p.getLinearVelocity());
	p.setAngularVelocity(iInvA*(rA.cross(J))+p.getAngularVelocity());

	q.setLinearVelocity(-J/mB+q.getLinearVelocity());
	q.setAngularVelocity(iInvB*(rB.cross(-J))+p.getAngularVelocity());
}

void Molecule::updateRotationMatrix(){
	Vector3 w = angularVelocity.normalize();
	Quaternion q = Quaternion(w, 1.0f);
	q.rotate(angularVelocity.length()*dt);
	//q = q.rotatedVector(angularVelocity);
	R =R*q.rotationMatrix();
	/*
	float V = sqrtf(w.y*w.y+w.z*w.z);
	float L = w.length();

	Matrix3 DR;
	std::cout<<"V: "<<V<<std::endl;
	if(V==0.0f){
		std::cout<<"v = 0\n";
		DR = Matrix3(
			1.0f, 0.0f, 0.0f,
			0.0f, cosf(L*dt), -sinf(L*dt),
			0.0f, sinf(L*dt), cosf(L*dt));

	}else{
		Matrix3 r = Matrix3(
			V/L, 0.0f, w.x/L,
			-(w.x*w.y)/(V*L), w.z, w.y/L,
			-(w.x*w.y)/(V*L), -w.y/V, w.z/L);

		Matrix3 rot = Matrix3(
			cosf(L*dt), -sinf(L*dt), 0.0f,
			sinf(L*dt), cosf(L*dt), 0.0f,
			0.0f, 0.0f, 1.0f);
		

		Matrix3 rt = Matrix3(
			V/L, -(w.x*w.y)/(V*L), -(w.x*w.y)/(V*L),
			0, w.z, -w.y/V,
			w.x/L, w.y/L, w.z/L);

		DR = r*rot*rt;
		//std::cout<<DR;
	}

	//update
	R = R*DR;
	//std::cout<<"RR: " <<Matrix4(R.toGLMatrix4());
	
	*/
	//update inertia tensor
	updateInertia();
}

void Molecule::updateInertia(){
	
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

