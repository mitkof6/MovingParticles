#ifndef PARTICLEWALLCONTAINER_H_H
#define PARTICLEWALLCONTAINER_H_H

#include "Particle.h"
#include "Wall.h"
#include "Constants.h"

class ParticleWallContainer{

public:
	ParticleWallContainer(Particle *p, Wall w);
	~ParticleWallContainer(void);

	bool checkCollision();
	Particle *getParticle();
	Wall getWall();
private:
	Particle *particle;
	Wall wall;
};

#endif
