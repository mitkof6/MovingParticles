#include "ParticlePairContainer.h"


ParticlePairContainer::ParticlePairContainer(Particle *p1, Particle *p2){
	particle1 = p1;
	particle2 = p2;
}


ParticlePairContainer::~ParticlePairContainer(void){

}

bool ParticlePairContainer::checkCollision(){//TODO
	float r = particle1->getRadius() + particle2->getRadius();
	Vector3D displacement = particle1->getPosition() - particle2->getPosition();
	if (displacement.magnitude() <= r) {

		Vector3D netVelocity = particle1->getVelocity() - particle2->getVelocity();
		return netVelocity.dot(displacement) > 0;

		return true;
	}else
		return false;
}

Particle *ParticlePairContainer::getP1(){
	return particle1;
}

Particle *ParticlePairContainer::getP2(){
	return particle2;
}
