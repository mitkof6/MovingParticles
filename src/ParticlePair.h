#ifndef PARTICLEPAIR_H_
#define PARTICLEPAIR_H_

#include "Particle.h"

class ParticlePair{

public:
	ParticlePair(Particle &p, Particle &q);
	~ParticlePair(void);

	
	bool equals(Particle &p, Particle &q);

	Particle* getParticle1();
	Particle* getParticle2();
private:
	Particle *p1, *p2;
};

#endif

