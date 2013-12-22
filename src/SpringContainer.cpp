#include "SpringContainer.h"

SpringContainer::SpringContainer() : AbstractContainer(){

}


SpringContainer::~SpringContainer(void){
	
}

void SpringContainer::add(DoubleSpring &ds){
	doubleSprings.push_back(ds);
}

void SpringContainer::draw(){

	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].draw();
	}
}

void SpringContainer::update(){
	wallCollisions.incTime();
	ballCollisions.incTime();

	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].update();
	}

	findWallCollisions();

	findSphereCollisions();

	wallCollisions.registerEvent();
	ballCollisions.registerEvent();
}


void SpringContainer::findWallCollisions(){

	for(unsigned i = 0;i<doubleSprings.size();i++){
		checkWall(doubleSprings[i].getP1());
		checkWall(doubleSprings[i].getP2());
	}

}

void SpringContainer::checkWall(Particle &p){
	Wall temp;
	if(collision.checkForWallCollision(
		p.getMassCenter(),p.getMassCenter(), p.getRadius(),
		temp)){
			
		wallCollisions.incCounter();
		wallCollisions.registerEvent();

		p.collisionHandler(temp.getWallDirection());

		wallCollisions.incCounter();
	}
}

void SpringContainer::findSphereCollisions(){
	
	for(unsigned i = 0;i<doubleSprings.size();i++){
		
		for(unsigned j = 0;j<doubleSprings.size();j++){
			
			if(j>i){
				checkSpheres(doubleSprings[i].getP1(), doubleSprings[j].getP1());
				checkSpheres(doubleSprings[i].getP1(), doubleSprings[j].getP2());
				checkSpheres(doubleSprings[i].getP2(), doubleSprings[j].getP1());
				checkSpheres(doubleSprings[i].getP2(), doubleSprings[j].getP2());

				checkSpheres(doubleSprings[i].getP1(), doubleSprings[i].getP2());
			}
		}
	}
}

void SpringContainer::checkSpheres(Particle &p, Particle &q){
	if(collision.checkForSpheresCollision(
		p.getMassCenter(), p.getMassCenter(), p.getRadius(),
		q.getMassCenter(), q.getRadius())){
					
		ballCollisions.incCounter();
		ballCollisions.registerEvent();

		p.collisionHandler(q, collisionMode);
		
		ballCollisions.incCounter();
	}
}
