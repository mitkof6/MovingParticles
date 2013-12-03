#include <ctime>
#include <stdlib.h>

#include "Viewer.h"
#include "Renderable.h"
#include "Constants.h"

#include "Particle.h"
#include "Box.h"
#include "Constants.h"
#include "ParticleContainer.h"

void generateParticles(ParticleContainer &pc);
float rand(float min, float max);

int main(int argc, char** argv){
	

	ParticleContainer pc = ParticleContainer();
	generateParticles(pc);
	Viewer viewer(argc, argv, pc);

	Renderable *box = new Box(1.0f, 1.0, 1.0, BOX_SIZE);
	viewer.addToDraw(box);

	viewer.start();

	//clean up
	delete box;

	return 0;
}

void generateParticles(ParticleContainer &pc){
	
	srand((unsigned)time(0));
	
	for(int i = 0;i<PARTICLES;i++){
		
		float mass = rand(MIN_M, MAX_M);
		float radius = mass/(MAX_M-MIN_M);

		Particle p = Particle(
				rand(0, 1),rand(0, 1),rand(0, 1),
				rand(MIN_X+radius, MAX_X-radius),
				rand(MIN_Y+radius, MAX_Y-radius),
				rand(MIN_Z+radius, MAX_Z-radius),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX), 
				radius,
				mass);
		p.setMatirial(
			rand(AB_MIN, AB_MAX), rand(AB_MIN, AB_MAX), rand(AB_MIN, AB_MAX), 1.0,
			rand(DI_MIN, DI_MAX), rand(DI_MIN, DI_MAX), rand(DI_MIN, AB_MAX), 1.0,
			rand(SP_MIN, SP_MAX), rand(SP_MIN, SP_MAX), rand(SP_MIN, AB_MAX), 1.0,
			rand(SH_MIN, SH_MAX));

		pc.add(p);
	}
}

float rand(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}


