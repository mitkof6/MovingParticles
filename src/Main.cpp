#include <ctime>
#include <iostream>

#include "Viewer.h"
#include "Renderable.h"
#include "Constants.h"

#include "Particle.h"
#include "Box.h"
#include "Constants.h"
#include "ParticleContainer.h"

void generateParticles(ParticleContainer *pc);
float rand(float min, float max);

int main(int argc, char** argv){
	Viewer viewer(argc, argv);

	Renderable *pc = new ParticleContainer();
	generateParticles((ParticleContainer *) pc);
	viewer.addToDraw(pc);

	Renderable *box = new Box(1.0f, 1.0f, 1.0f, BOX_SIZE);
	viewer.addToDraw(box);

	viewer.start();

	//clean up
	delete pc;
	delete box;

	return 0;
}

void generateParticles(ParticleContainer *pc){
	
	srand(time(0));
	
	for(int i = 0;i<PARTICLES;i++){
		
		float radius = rand(MIN_R, MAX_R);

		Particle p = Particle(
				rand(0, 1),rand(0, 1),rand(0, 1),
				rand(MIN_X+radius, MAX_X-radius),
				rand(MIN_Y+radius, MAX_Y-radius),
				rand(MIN_Z+radius, MAX_Z-radius),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX), 
				radius,
				rand(MIN_M, MAX_M));

		((ParticleContainer *)pc)->add(p);
	}
}

float rand(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}


