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

	findParticleParticleCollisions();
}

void ParticleContainer::findWallCollisions(){

	for(unsigned i = 0;i<particles.size();i++){
		Wall temp;
		if(checkForCollision(particles[i], temp)){
			
			wallCollisions.incCounter();
			wallCollisions.registerEvent();

			particles[i].collisionHandler(temp.getWallDirection());
		}
	}

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

bool ParticleContainer::checkForCollision(Particle &p, Wall &w){
	Vector3 pos = p.getMassCenter();
	float r = p.getRadius();

	if(pos.x-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.x-r);
		p.setMassCenter(pos+Vector3(dis, 0, 0));

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.x+r);
		p.setMassCenter(pos+Vector3(dis, 0, 0));

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.y-r);
		p.setMassCenter(pos+Vector3(0, dis, 0));

		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.y+r);
		p.setMassCenter(pos+Vector3(0, dis, 0));

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.z-r);
		p.setMassCenter(pos+Vector3(0, 0, dis));

		w = Wall(WALL_FAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.z+r);
		p.setMassCenter(pos+Vector3(0, 0, dis));

		w = Wall(WALL_NEAR);
		
	}else{
		return false;
	}

	return true;
}

void ParticleContainer::findParticleParticleCollisions(){
	
	for(unsigned i = 0;i<particles.size();i++){
		
		for(unsigned j = 0;j<particles.size();j++){
			
			if(j>i){
				if(checkForCollision(particles[i], particles[j])){
					
					ballCollisions.incCounter();
					ballCollisions.registerEvent();

					particles[i].collisionHandler(particles[j], collisionMode);

				}
			}
		}
	}
}

bool ParticleContainer::checkForCollision(Particle &p, Particle &q){
	Vector3 displacement = p.getMassCenter()-q.getMassCenter();

	float r = (p.getRadius()+q.getRadius());

	if(displacement.lengthSq()<r*r){
		return true;
	}else{

		return false;
	}

}


