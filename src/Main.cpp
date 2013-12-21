#include <ctime>
#include <stdlib.h>

#include "Viewer.h"
#include "Renderable.h"
#include "Constants.h"

#include "ParticleContainer.h"
#include "Particle.h"

#include "MoleculeContainer.h"
#include "Molecule.h"

#include "SpringContainer.h"
#include "DoubleSpring.h"

#include "MixedSystem.h"

#include "Box.h"
#include "Constants.h"


void generateParticles(AbstractContainer *pc, int size);
void generateMolecules(AbstractContainer *rbc, int size);
void generateSpringSystems(AbstractContainer *sc, int size);

float rand(float min, float max);

int main(int argc, char** argv){
	
	srand((unsigned)time(NULL));

	Viewer viewer(argc, argv);

	//molecule or particles
	if(MOLECULE){
		AbstractContainer *container =
				new MoleculeContainer();
		generateMolecules(container, MOLECULES);
		viewer.setContainer(container);
		
	}else if(PARTICLE){
		AbstractContainer *container =
				new ParticleContainer(BALL_COLLISION_REAL_MODE);
		generateParticles(container, PARTICLES);
		viewer.setContainer(container);
	}else{
		SpringContainer springContainer = SpringContainer();
		generateSpringSystems(&springContainer, SPRING_SYSTEMS);

		MoleculeContainer moleculeContainer = MoleculeContainer();
		generateMolecules(&moleculeContainer, MOLECULES);

		AbstractContainer *container = 
			new MixedSystem(springContainer, moleculeContainer);

		viewer.setContainer(container);
	}

	//bounding box
	Renderable *box = new Box(1.0f, 1.0, 1.0, BOX_SIZE);
	viewer.addToDraw(box);

	//begin rendering
	viewer.start();

	//clean up
	delete box;

	system("pause");
	return 0;
}

void generateSpringSystems(AbstractContainer *sc, int size){
	for(int i = 0;i<size;i++){

		((SpringContainer *)sc)->add(DoubleSpring());
	}
}

void generateMolecules(AbstractContainer *rbc, int size){
	for(int i = 0;i<size;i++){

		((MoleculeContainer *)rbc)->add(Molecule(MOLECULES_MAX));
	}
}

void generateParticles(AbstractContainer *pc, int size){
	
	for(int i = 0;i<size;i++){
		
		float mass = rand(MASS_MIN, MASS_MAX);
		float radius = mass/(MASS_MAX-MASS_MIN);

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

		((ParticleContainer *)pc)->add(p);
	}
}

float rand(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}


