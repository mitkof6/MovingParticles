#ifndef PARTICLEPAIRCONTAINER_H_
#define PARTICLEPAIRCONTAINER_H_

#include "Particle.h"

class ParticlePairContainer{

public:
	ParticlePairContainer(Particle *p1, Particle *p2);
	~ParticlePairContainer(void);

	bool checkCollision();

	Particle *getP1();
	Particle *getP2();

private:
	Particle *particle1, *particle2;
};

#endif

