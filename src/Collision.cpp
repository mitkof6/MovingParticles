#include "Collision.h"


Collision::Collision(void)
{
}


Collision::~Collision(void){

}


bool Collision::checkForWallCollision(Vector3 &massCenter, const Vector3 &pos, float r, Wall &w){

	if(pos.x-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.x-r);
		//p.setMassCenter(pos+Vector3(dis, 0, 0));
		massCenter = massCenter+Vector3(dis, 0, 0);

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.x+r);
		//p.setMassCenter(pos+Vector3(dis, 0, 0));
		massCenter = massCenter+Vector3(dis, 0, 0);

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.y-r);
		//p.setMassCenter(pos+Vector3(0, dis, 0));
		massCenter = massCenter+Vector3(0, dis, 0);

		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.y+r);
		//p.setMassCenter(pos+Vector3(0, dis, 0));
		massCenter = massCenter+Vector3(0, dis, 0);

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.z-r);
		//p.setMassCenter(pos+Vector3(0, 0, dis));
		massCenter = massCenter+Vector3(0, 0, dis);

		w = Wall(WALL_FAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.z+r);
		//p.setMassCenter(pos+Vector3(0, 0, dis));
		massCenter = massCenter+Vector3(0, 0, dis);

		w = Wall(WALL_NEAR);
		
	}else{
		return false;
	}

	return true;
}

bool Collision::checkForSpheresCollision(Vector3 &massCenter, const Vector3 &p, float r1, const Vector3 &q, float r2){
	Vector3 displacement = p-q;

	float r = (r1+r2);

	if(displacement.lengthSq()<r*r){
		//correction
		Vector3 displacement = p-q;
		float dr = (r1+r2-displacement.length())/2;
		Vector3 n = displacement.normalize();
		massCenter = massCenter+n*dr;

		return true;
	}else{

		return false;
	}

}


void Collision::handleWallCollision(
	const Vector3 &massCenterA, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
	const Vector3 &cp, const Vector3 &cn){

	Vector3 rA = cp - massCenterA;
	
	float j = impulseMagnitude(
		vA, wA, rA, iInvA, mA,
		cn); 
	
	Vector3 J = j*cn;
	//std::cout<<"J "<<J<<std::endl;
	//std::cout<<"Total before: "<<m.getLinearVelocity().length()+m.getAngularVelocity().length()<<std::endl;

	vA = vA + J/mA;
	
	wA = wA + iInvA*(rA.cross(J));

	//std::cout<<"Total after: "<<m.getLinearVelocity().length()+m.getAngularVelocity().length()<<std::endl;

}

void Collision::handleSphereCollision(
		const Vector3 &massCenterA, Vector3 &vA, Vector3 &wA, const Matrix3 iInvA, float mA,
		const Vector3 &massCenterB, Vector3 &vB, Vector3 &wB, const Matrix3 iInvB, float mB,
		const Vector3 &cp, const Vector3 &cn, float gain){

	Vector3 rA = cp - massCenterA;
	
	Vector3 rB = cp - massCenterB;
	
	float j = impulseMagnitude(
		vA, wA, rA, iInvA, mA,
		vB, wB, rB, iInvB, mB,
		cn); 
	
	Vector3 J = j*cn;
	
	vA = vA + J/mA;
	wA = (wA + iInvA*(rA.cross(J)))*gain;

	vB = vB - J/mB;
	wB = (wB + iInvB*(rB.cross(-J)))*gain;

}

void Collision::calculateCollisionPoint(
	const Vector3 &p1, float r1,
	const Vector3 &p2, float r2,
	Vector3 &cp, Vector3 &cn){

	float t = r1/(r1+r2);

	cp = p1+(p2-p1)*t;
	cn = (p2-p1).normalize()*(-1);
}

float Collision::impulseMagnitude(
	const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
	const Vector3 &vB, const Vector3 &wB, const Vector3 &rB, const Matrix3 &iInvB, float mB,
	const Vector3 &n){

	float j = 
		(-2*(vA+wA.cross(rA)-vB-wB.cross(rB)).dot(n))/
		(((iInvA*(rA.cross(n))).cross(rA)+(iInvB*(rB.cross(n))).cross(rB)).dot(n) +1/mA+1/mB);


	return j;
}

float Collision::impulseMagnitude(
	const Vector3 &vA, const Vector3 &wA, const Vector3 &rA, const Matrix3 &iInvA, float mA,
	const Vector3 &n){

	
	float j = 
		(-2*(vA+wA.cross(rA)).dot(n))/
		(((iInvA*(rA.cross(n))).cross(rA)).dot(n) +1/mA);

	return j;
}
