
//-lGL -lglut -GLU

#include <ctime>

#include "Viewer.h"
#include "Renderable.h"
#include "Constants.h"

#include "Particle.h"
#include "Box.h"
#include "Constants.h"
#include "Octree.h"

Renderable *octree = new Octree(
	Vector3D(-BOX_SIZE / 2, -BOX_SIZE / 2, -BOX_SIZE / 2),
    Vector3D(BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE / 2), 1);

void generateParticles(Viewer &v);
float rand(float min, float max);

int main(int argc, char** argv){
	Viewer viewer(argc, argv);

	generateParticles(viewer);
	viewer.addToDraw(octree);

	Renderable *box = new Box(1.0f, 1.0f, 1.0f, BOX_SIZE);
	viewer.addToDraw(box);

	viewer.start();

	//TODO
	delete box;
	delete octree;

	return 0;
}

void generateParticles(Viewer &v){

	srand(time(0));
	
	for(int i = 0;i<PARTICLES;i++){
		
		float radius = rand(MIN_R, MAX_R);

		Renderable *p = new Particle(
				rand(0, 1),rand(0, 1),rand(0, 1),
				rand(MIN_X+radius, MAX_X-radius),
				rand(MIN_Y+radius, MAX_Y-radius),
				rand(MIN_Z+radius, MAX_Z-radius),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX),
				rand(MIN_VX, MAX_VX), 
				radius,
				rand(MIN_M, MAX_M));
		//((Particle *)p)->getPosition().toString();
		
		((Octree *)octree)->add(*(Particle *) p);
		//v.addToDraw(p);
	}




}

float rand(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}


