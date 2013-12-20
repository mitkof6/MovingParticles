#include "SpringContainer.h"


SpringContainer::SpringContainer() : ParticleContainer(){

}


SpringContainer::~SpringContainer(void){
	
}

void SpringContainer::add(DoubleSpring &ds){
	doubleSprings.push_back(ds);

	
	ParticleContainer::add(ds.getP1());
	ParticleContainer::add(ds.getP2());
}

void SpringContainer::draw(){
	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].draw();
	}
}

void SpringContainer::update(){
	wallCollisions.incTime();
	ballCollisions.incTime();

	if(thirdPerson){
		camera.update();
	}

	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].update();
	}


	findWallCollisions();

	findParticleParticleCollisions();

}

