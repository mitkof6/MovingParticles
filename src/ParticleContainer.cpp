#include "ParticleContainer.h"


ParticleContainer::ParticleContainer(void){

}


ParticleContainer::~ParticleContainer(void){

}

void ParticleContainer::add(Particle p){
	particles.push_back(p);
}

void ParticleContainer::draw(){
	for(unsigned i = 0;i<particles.size();i++){
		particles[i].draw();
	}
}

void ParticleContainer::update(){
	for(unsigned i = 0;i<particles.size();i++){
		particles[i].update();
	}

	resolveRepaitedCollisions();

	findWallCollisions();

	findParticleParticleCollisions();

}

void ParticleContainer::findWallCollisions(){

	for(unsigned i = 0;i<particles.size();i++){
		Wall temp;
		if(checkForCollision(particles[i], temp)){
			particles[i].collisionHandler(temp.getWallDirection());
		}
	}

}

bool ParticleContainer::checkForCollision(Particle &p,Wall &w){
	Vector3D pos = p.getPosition();
	float r = p.getRadius();

	if(pos.x-r<=-BOX_SIZE/2){
		w = Wall(WALL_LEFT);
		return true;
	}else if(pos.x+r>=BOX_SIZE/2){
		w = Wall(WALL_RIGHT);
		return true;
	}else if(pos.y-r<=-BOX_SIZE/2){
		w = Wall(WALL_BOTTOM);
		return true;
	}else if(pos.y+r>=BOX_SIZE/2){
		w = Wall(WALL_TOP);
		return true;
	}else if(pos.z-r<=-BOX_SIZE/2){
		w = Wall(WALL_NEAR);
		return true;
	}else if(pos.z+r>=BOX_SIZE/2){
		w = Wall(WALL_FAR);
		return true;
	}else{
		return false;
	}
}

void ParticleContainer::findParticleParticleCollisions(){
	
	bool collisionRepeated = false;
	for(unsigned i = 0;i<particles.size();i++){
		
		for(unsigned j = 0;j<particles.size();j++){
			
			if(j>i){
				if(checkForCollision(particles[i], particles[j])){
					for(unsigned k = 0;k<collisionPairs.size();k++){
						if(collisionPairs[k].equals(particles[i], particles[j])){
							collisionRepeated = true;
							break;
						}
					}
					
					if(collisionRepeated){
						collisionRepeated = false;
						continue;
					}

					particles[i].collisionHandler(particles[j]);
					particles[j].collisionHandler(particles[i]);

					collisionPairs.push_back(ParticlePair(particles[i], particles[j]));
					std::cout<<"Add Size: "<<collisionPairs.size()<<"\n";
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

void ParticleContainer::resolveRepaitedCollisions(){
	for(unsigned i = 0;i<collisionPairs.size();i++){
		if(!checkForCollision(*collisionPairs[i].getParticle1(), 
			*collisionPairs[i].getParticle2())){
			
			collisionPairs.erase(collisionPairs.begin()+i);
			std::cout<<"Size: "<<collisionPairs.size()<<"\n";
		}
	}
}

