#include <ctime>
#include <stdlib.h>

#include "Viewer.h"
#include "Renderable.h"
#include "Constants.h"

#include "SphereContainer.h"
#include "Sphere.h"

#include "MoleculeContainer.h"
#include "Molecule.h"

#include "SpringContainer.h"
#include "DoubleSpring.h"

#include "MixedSystem.h"

#include "Box.h"
#include "Constants.h"

#include "Grid.h"

/**
 * Populates a sphere container with spheres
 *
 * @param (pointer to abstract container, # of particles)
 */
void generateParticles(AbstractContainer *sc, int n);

/**
 * Populates a moleclue's container with molecules
 *
 * @param (pointer to abstract container, # of particles)
 */
void generateMolecules(AbstractContainer *rbc, int n);

/**
 * Populates a spring container with springs
 *
 * @param (pointer to abstract container, # of particles)
 */
void generateSpringSystems(AbstractContainer *sc, int n);

/**
 * Generates random number between [min-max]
 *
 * @param (min, max)
 */
float randMM(float min, float max);


/**
 * Entry point
 */
int main(int argc, char** argv){
	
	srand((unsigned)time(NULL));

	//renderer
	Viewer viewer(argc, argv);

	//molecules
	AbstractContainer *molecules =
				new MoleculeContainer();
	generateMolecules(molecules, MOLECULES);
	viewer.addContainer(molecules);

	//spheres
	AbstractContainer *spheres =
				new SphereContainer(BALL_COLLISION_REAL_MODE);
	generateParticles(spheres, PARTICLES);
	viewer.addContainer(spheres);

	//mixed
	SpringContainer springContainer = SpringContainer();
	generateSpringSystems(&springContainer, SPRING_SYSTEMS);

	MoleculeContainer moleculeContainer = MoleculeContainer();
	generateMolecules(&moleculeContainer, MOLECULES);

	AbstractContainer *mixedSystem = 
			new MixedSystem(springContainer, moleculeContainer);

	viewer.addContainer(mixedSystem);


	
	//Renderable *grid = new Grid(3, 3);
	//viewer.addToDraw(grid);

	//bounding box
	Renderable *box = new Box(1.0f, 1.0, 1.0, BOX_SIZE);
	viewer.addToDraw(box);

	//begin rendering
	viewer.start();

	//clean up
	delete box;
	delete molecules;
	delete spheres;
	delete mixedSystem;

	return 0;
}

void generateSpringSystems(AbstractContainer *sc, int n){
	for(int i = 0;i<n;i++){

		((SpringContainer *)sc)->add(DoubleSpring());
	}
}

void generateMolecules(AbstractContainer *rbc, int n){
	for(int i = 0;i<n;i++){

		((MoleculeContainer *)rbc)->add(Molecule(MOLECULES_MAX));
	}
}

void generateParticles(AbstractContainer *sc, int n){
	
	for(int i = 0;i<n;i++){
		
		float mass = randMM(MASS_MIN, MASS_MAX);
		float radius = mass/(MASS_MAX-MASS_MIN);

		Sphere p = Sphere(
				randMM(0, 1),randMM(0, 1),randMM(0, 1),
				randMM(MIN_X+radius, MAX_X-radius),
				randMM(MIN_Y+radius, MAX_Y-radius),
				randMM(MIN_Z+radius, MAX_Z-radius),
				randMM(MIN_VX, MAX_VX),
				randMM(MIN_VX, MAX_VX),
				randMM(MIN_VX, MAX_VX), 
				radius,
				mass);
		p.setMatirial(
			randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
			randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
			randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
			randMM(SH_MIN, SH_MAX));

		((SphereContainer *)sc)->add(p);
	}
}

float randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}


