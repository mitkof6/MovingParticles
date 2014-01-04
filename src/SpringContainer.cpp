#include "SpringContainer.h"

SpringContainer::SpringContainer() : AbstractContainer(){

}


SpringContainer::~SpringContainer(void){
	
}

void SpringContainer::add(DoubleSpring ds){
	doubleSprings.push_back(ds);
}

void SpringContainer::draw(){

	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].draw();
	}
}

void SpringContainer::update(){
	//histogram time
	wallCollisionCounter.incTime();
	sphereCollisionCounter.incTime();

	//update state
	for(unsigned i = 0;i<doubleSprings.size();i++){
		doubleSprings[i].update();
	}

	//find collisions
	findWallCollisions();
	findSphereCollisions();

	//register histogram
	wallCollisionCounter.registerEvent();
	sphereCollisionCounter.registerEvent();
}


void SpringContainer::findWallCollisions(){

	for(unsigned i = 0;i<doubleSprings.size();i++){
		checkWall(doubleSprings[i].getSphereOne());
		checkWall(doubleSprings[i].getSphereTwo());
	}

}

void SpringContainer::checkWall(Sphere &p){
	Wall temp;
	if(collision.checkForWallCollision(
		p.getMassCenter(),p.getMassCenter(), p.getRadius(),
		temp)){
			
		//handle collision
		p.collisionHandler(temp.getWallDirection());

		//inc counter
		wallCollisionCounter.incCounter();
	}
}

void SpringContainer::findSphereCollisions(){
	
	for(unsigned i = 0;i<doubleSprings.size();i++){
		
		for(unsigned j = 0;j<doubleSprings.size();j++){
			
			if(j>i){
				checkSpheres(doubleSprings[i].getSphereOne(), doubleSprings[j].getSphereOne());
				checkSpheres(doubleSprings[i].getSphereOne(), doubleSprings[j].getSphereTwo());
				checkSpheres(doubleSprings[i].getSphereTwo(), doubleSprings[j].getSphereOne());
				checkSpheres(doubleSprings[i].getSphereTwo(), doubleSprings[j].getSphereTwo());

				checkSpheres(doubleSprings[i].getSphereOne(), doubleSprings[i].getSphereTwo());
			}
		}
	}
}

void SpringContainer::checkSpheres(Sphere &p, Sphere &q){
	if(collision.checkForSpheresCollision(
		p.getMassCenter(), p.getMassCenter(), p.getRadius(),
		q.getMassCenter(), q.getRadius())){

		//handle collision
		p.collisionHandler(q, collisionMode);
		
		//inc counter
		sphereCollisionCounter.incCounter();
	}
}
