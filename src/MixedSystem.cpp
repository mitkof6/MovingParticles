#include "MixedSystem.h"


MixedSystem::MixedSystem(SpringContainer &sC, MoleculeContainer &mC){
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
	wallCollisions.incTime();
	ballCollisions.incTime();

	moleculeContainer.update();
	springContainer.update();

	resolveSystemCollisions();

	//sync
	//std::cout<<moleculeContainer.getWallCollisionCounter().getCounter()<<std::endl;
	wallCollisions.add(moleculeContainer.getWallCollisionCounter().getDifference());
	wallCollisions.add(springContainer.getWallCollisionCounter().getDifference());
	ballCollisions.add(moleculeContainer.getBallCollisionCounter().getDifference());
	ballCollisions.add(springContainer.getBallCollisionCounter().getDifference());

	wallCollisions.registerEvent();
	ballCollisions.registerEvent();
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
		//std::cout<<"Collision"<<std::endl;				
		//find collision point
		Vector3 cp, cn;
		collision.calculateCollisionPoint(
			p.getMassCenter(), p.getRadius(),
			m.getMassCenter()+m.getDisplacement(k), m.getRadius(k),
			cp, cn);

		//std::cout<<cp<<std::endl;

		//handle collision
		collision.handleSphereCollision(
			p.getMassCenter(), p.getLinearVelocity(), p.getAngularVelocity(), p.getInertiaInv(), p.getMass(),
			m.getMassCenter(), m.getLinearVelocity(), m.getAngularVelocity(), m.getInertiaInv(), m.getMass(),
			cp, cn,
			GAIN);

		ballCollisions.incCounter();
	}
}
