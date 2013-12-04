#include "ParticleContainer.h"


ParticleContainer::ParticleContainer() : AbstractContainer(){

}


ParticleContainer::~ParticleContainer(void){

}

void ParticleContainer::add(Particle p){
	particles.push_back(p);
}

void ParticleContainer::saveWallCollisions(){
	wallCollisions.saveToMat(WALL_COLLISION_PATH);
}

void ParticleContainer::saveBallCollisions(){
	ballCollisions.saveToMat(BALL_COLLISION_PATH);
}

void ParticleContainer::draw(){
	for(unsigned i = 0;i<particles.size();i++){
		particles[i].draw();
	}
}

void ParticleContainer::update(){
	wallCollisions.incTime();
	ballCollisions.incTime();

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

bool ParticleContainer::checkForCollision(Particle &p, Wall &w){
	Vector3D pos = p.getPosition();
	float r = p.getRadius();

	if(pos.x-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.x-r);
		p.setPosition(pos+Vector3D(dis, 0, 0));

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.x+r);
		p.setPosition(pos+Vector3D(dis, 0, 0));

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.y-r);
		p.setPosition(pos+Vector3D(0, dis, 0));

		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.y+r);
		p.setPosition(pos+Vector3D(0, dis, 0));

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.z-r);
		p.setPosition(pos+Vector3D(0, 0, dis));

		w = Wall(WALL_NEAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.z+r);
		p.setPosition(pos+Vector3D(0, 0, dis));

		w = Wall(WALL_FAR);
		
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

					particles[i].collisionHandler(particles[j]);

				}
			}
		}
	}
}

bool ParticleContainer::checkForCollision(Particle &p, Particle &q){
	Vector3D displacement = p.getPosition()-q.getPosition();

	float r = (p.getRadius()+q.getRadius());

	if(displacement.magnitudeSquared()<r*r){
		return true;
	}else{

		return false;
	}

}


