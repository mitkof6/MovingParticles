#include "ParticleContainer.h"

ParticleContainer::ParticleContainer() : AbstractContainer(true){
	
}

ParticleContainer::ParticleContainer(bool collisionMode) : AbstractContainer(collisionMode){
	
}


ParticleContainer::~ParticleContainer(void){

}

void ParticleContainer::add(Particle &p){
	particles.push_back(p);
}

void ParticleContainer::draw(){
	if(thirdPerson){
		camera.draw();
	}

	for(unsigned i = 0;i<particles.size();i++){
		particles[i].draw();
	}
}

void ParticleContainer::update(){
	wallCollisions.incTime();
	ballCollisions.incTime();

	if(thirdPerson){
		camera.update();
	}

	for(unsigned i = 0;i<particles.size();i++){
		particles[i].update();
	}

	findWallCollisions();

	findSphereCollisions();
}

void ParticleContainer::enable3rdPerson(){
	thirdPerson = !thirdPerson;
	camera.lock(particles[target].getMassCenter());

}

void ParticleContainer::changeTargert(){
	target++;
	if(target==particles.size()){
		target = 0;
	}
	camera.lock(particles[target].getMassCenter());

}

void ParticleContainer::findWallCollisions(){

	for(unsigned i = 0;i<particles.size();i++){
		Wall temp;
		if(collision.checkForWallCollision(
			particles[i].getMassCenter(),particles[i].getMassCenter(), particles[i].getRadius(),
			temp)){
			
			wallCollisions.incCounter();
			wallCollisions.registerEvent();

			particles[i].collisionHandler(temp.getWallDirection());
		}
	}

}

void ParticleContainer::findSphereCollisions(){
	
	for(unsigned i = 0;i<particles.size();i++){
		
		for(unsigned j = 0;j<particles.size();j++){
			
			if(j>i){
				if(collision.checkForSpheresCollision(
					particles[i].getMassCenter(), particles[i].getMassCenter(), particles[i].getRadius(),
					particles[j].getMassCenter(), particles[j].getRadius())){
					
					ballCollisions.incCounter();
					ballCollisions.registerEvent();

					particles[i].collisionHandler(particles[j], collisionMode);

				}
			}
		}
	}
}
