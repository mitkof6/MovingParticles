#include "SphereContainer.h"

SphereContainer::SphereContainer() : AbstractContainer(true){
	
}

SphereContainer::SphereContainer(bool collisionMode) : AbstractContainer(collisionMode){
	
}


SphereContainer::~SphereContainer(void){

}

void SphereContainer::add(Sphere &p){
	spheres.push_back(p);
}

void SphereContainer::draw(){
	if(thirdPerson){
		camera.draw();
	}

	for(unsigned i = 0;i<spheres.size();i++){
		spheres[i].draw();
	}
}

void SphereContainer::update(){
	//histogram time
	wallCollisionCounter.incTime();
	sphereCollisionCounter.incTime();

	//3rd person
	if(thirdPerson){
		camera.update();
	}

	//update states
	for(unsigned i = 0;i<spheres.size();i++){
		spheres[i].update();
	}

	//check for collisions
	findWallCollisions();
	findSphereCollisions();

	//register histogram
	wallCollisionCounter.registerEvent();
	sphereCollisionCounter.registerEvent();
}

void SphereContainer::enable3rdPerson(){
	thirdPerson = !thirdPerson;
	camera.lock(spheres[target].getMassCenter());

}

void SphereContainer::changeTargert(){
	target++;
	if(target==spheres.size()){
		target = 0;
	}
	camera.lock(spheres[target].getMassCenter());

}

void SphereContainer::findWallCollisions(){

	for(unsigned i = 0;i<spheres.size();i++){
		Wall temp;
		if(collision.checkForWallCollision(
			spheres[i].getMassCenter(),spheres[i].getMassCenter(), spheres[i].getRadius(),
			temp)){

			//handle wall collision
			spheres[i].collisionHandler(temp.getWallDirection());

			//inc counter
			wallCollisionCounter.incCounter();
		}
	}

}

void SphereContainer::findSphereCollisions(){
	
	for(unsigned i = 0;i<spheres.size();i++){
		
		for(unsigned j = 0;j<spheres.size();j++){
			
			if(j>i){
				if(collision.checkForSpheresCollision(
					spheres[i].getMassCenter(), spheres[i].getMassCenter(), spheres[i].getRadius(),
					spheres[j].getMassCenter(), spheres[j].getRadius())){
					
					//handle spheres collision
					spheres[i].collisionHandler(spheres[j], collisionMode);

					//inc counter
					sphereCollisionCounter.incCounter();
				}
			}
		}
	}
}
