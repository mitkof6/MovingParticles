#include "ParticleWallContainer.h"


ParticleWallContainer::ParticleWallContainer(Particle *p, Wall w){
	particle = p;
	wall = w;
}


ParticleWallContainer::~ParticleWallContainer(void){
	
}

bool ParticleWallContainer::checkCollision(){
	Vector3D wallDir = wall.getWallDirection();

	return particle->getPosition().dot(wallDir)+particle->getRadius()>BOX_SIZE/2 &&
		particle->getVelocity().dot(wallDir)>0;
}

Particle *ParticleWallContainer::getParticle(){
	return particle;
}

Wall ParticleWallContainer::getWall(){
	return wall;
}
