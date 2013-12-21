#include "MixedSystem.h"


MixedSystem::MixedSystem(SpringContainer &sC, MoleculeContainer &mC) : AbstractContainer(){
	springContainer = sC;
	moleculeContainer = mC;
}


MixedSystem::~MixedSystem(void){

}

void MixedSystem::draw(){
	
	moleculeContainer.draw();
	springContainer.draw();
}
	
void MixedSystem::update(){
	//inc histogram time
	wallCollisionCounter.incTime();
	sphereCollisionCounter.incTime();

	moleculeContainer.update();
	springContainer.update();

	//resolve system->system collisions
	resolveSystemCollisions();

	//sync collision counter
	wallCollisionCounter.add(moleculeContainer.getWallCollisionCounter().getDifference());
	wallCollisionCounter.add(springContainer.getWallCollisionCounter().getDifference());
	sphereCollisionCounter.add(moleculeContainer.getSphereCollisionCounter().getDifference());
	sphereCollisionCounter.add(springContainer.getSphereCollisionCounter().getDifference());

	//register collisions
	wallCollisionCounter.registerEvent();
	sphereCollisionCounter.registerEvent();
}

void MixedSystem::enable3rdPerson(){
	moleculeContainer.enable3rdPerson();
}
	
void MixedSystem::changeTargert(){
	moleculeContainer.changeTargert();
}

void MixedSystem::resolveSystemCollisions(){
	
	for(unsigned i = 0;i<moleculeContainer.molecules.size();i++){

		for(unsigned j = 0;j<springContainer.doubleSprings.size();j++){

			for(int k = 0;k<moleculeContainer.molecules[i].getMoleculeCount();k++){
				
				checkSpheres(springContainer.doubleSprings[j].getSphereOne(), moleculeContainer.molecules[i], k);	
				checkSpheres(springContainer.doubleSprings[j].getSphereTwo(), moleculeContainer.molecules[i], k);
				
			}
		}
	}
}

void MixedSystem::checkSpheres(Sphere &p, Molecule &m, int k){
	if(collision.checkForSpheresCollision(
		p.getMassCenter(), p.getMassCenter(), p.getRadius(),
		m.getMassCenter()+m.getDisplacement(k), m.getRadius(k))){

		//find collision point
		Vector3 cp, cn;
		collision.calculateCollisionPoint(
			p.getMassCenter(), p.getRadius(),
			m.getMassCenter()+m.getDisplacement(k), m.getRadius(k),
			cp, cn);

		//handle collision
		collision.handleSphereCollision(
			p.getMassCenter(), p.getLinearVelocity(), p.getAngularVelocity(), p.getInertiaInv(), p.getMass(),
			m.getMassCenter(), m.getLinearVelocity(), m.getAngularVelocity(), m.getInertiaInv(), m.getMass(),
			cp, cn,
			GAIN);

		//inc collision
		sphereCollisionCounter.incCounter();
	}
}
