#include "ParticlePair.h"


ParticlePair::ParticlePair(Particle &p, Particle &q){
	p1 = &p;
	p2 = &q;
}


ParticlePair::~ParticlePair(void){

}

bool ParticlePair::equals(Particle &p, Particle &q){
	if(p==*p1 && q == *p2){
		return true;
	}else{
		return false;
	}
}

Particle* ParticlePair::getParticle1(){
	return p1;
}

Particle* ParticlePair::getParticle2(){
	return p2;
}
