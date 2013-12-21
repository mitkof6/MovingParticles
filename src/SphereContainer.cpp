#include "SphereContainer.h"

SphereContainer::SphereContainer() : AbstractContainer(true){
	
}

SphereContainer::SphereContainer(bool collisionMode) : AbstractContainer(collisionMode){
	
}


SphereContainer::~SphereContainer(void){

}

void SphereContainer::add(Sphere &p){
	particles.push_back(p);
}

void SphereContainer::draw(){
	if(thirdPerson){
		camera.draw();
	}

	for(unsigned i = 0;i<particles.size();i++){
		particles[i].draw();
	}
}

void SphereContainer::update(){
	wallCollisionCounter.incTime();
	sphereCollisionCounter.incTime();

	if(thirdPerson){
		camera.update();
	}

	for(unsigned i = 0;i<particles.size();i++){
		particles[i].update();
	}

	findWallCollisions();

	findSphereCollisions();

	wallCollisionCounter.registerEvent();
	sphereCollisionCounter.registerEvent();
}

void SphereContainer::enable3rdPerson(){
	thirdPerson = !thirdPerson;
	camera.lock(particles[target].getMassCenter());

}

void SphereContainer::changeTargert(){
	target++;
	if(target==particles.size()){
		target = 0;
	}
	camera.lock(particles[target].getMassCenter());

}

void SphereContainer::findWallCollisions(){

	for(unsigned i = 0;i<particles.size();i++){
		Wall temp;
		if(collision.checkForWallCollision(
			particles[i].getMassCenter(),particles[i].getMassCenter(), particles[i].getRadius(),
			temp)){

			particles[i].collisionHandler(temp.getWallDirection());

			wallCollisionCounter.incCounter();
		}
	}

}

void SphereContainer::findSphereCollisions(){
	
	for(unsigned i = 0;i<particles.size();i++){
		
		for(unsigned j = 0;j<particles.size();j++){
			
			if(j>i){
				if(collision.checkForSpheresCollision(
					particles[i].getMassCenter(), particles[i].getMassCenter(), particles[i].getRadius(),
					particles[j].getMassCenter(), particles[j].getRadius())){
					
					particles[i].collisionHandler(particles[j], collisionMode);

					sphereCollisionCounter.incCounter();
				}
			}
		}
	}
}
