#include "RigidBody.h"


RigidBody::RigidBody(void){

}


RigidBody::~RigidBody(void){

}

Vector3 &RigidBody::getMassCenter() {
	return x;
}

void RigidBody::setMassCenter(Vector3 c){
	x = c;
}

Vector3 RigidBody::getLinearVelocity() const{
	return v;
}

void RigidBody::setLinearVelocity(Vector3 vv){
	v = vv;
}

Vector3 RigidBody::getAngularVelocity() const{
	return omega;
}

void RigidBody::setAngularVelocity(Vector3 w){
	omega = w;
}

float RigidBody::getMass() const{
	return mass;
}

Matrix3 RigidBody::getInertia() const{
	return inertia;
}

Matrix3 RigidBody::getInertiaInv() const{
	return inertiaInv;
}

Matrix3 RigidBody::getOrientation() const{
	return orientation;
}

void RigidBody::applayForce(Vector3 f){
	totalForce = totalForce + f;
}

void RigidBody::clearForce(){
	totalForce = Vector3(0, 0, 0);
}

Vector3 RigidBody::getTotalForce() const{
	return totalForce;
}
