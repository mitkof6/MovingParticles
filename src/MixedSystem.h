#ifndef MIXEDSYSTEM_H_
#define MIXEDSYSTEM_H_

#include "AbstractContainer.h"
#include "Renderable.h"

#include "MoleculeContainer.h"
#include "SpringContainer.h"

using namespace std;

class MixedSystem : public AbstractContainer{
public:
	MixedSystem(SpringContainer &sC, MoleculeContainer &mC);
	~MixedSystem(void);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();

private:
	SpringContainer springContainer;
	MoleculeContainer moleculeContainer;

	void resolveSystemCollisions();
	void checkSpheres(Sphere &p, Molecule &m, int k);
};

#endif

