#ifndef MIXEDSYSTEM_H_
#define MIXEDSYSTEM_H_

#include "AbstractContainer.h"

#include "MoleculeContainer.h"
#include "SpringContainer.h"

using namespace std;

/**
 * Composition of molecules and double springs
 */
class MixedSystem : public AbstractContainer{
public:
	/**
	 * Constructor
	 *
	 * @param (spring container, molecule container)
	 */
	MixedSystem(SpringContainer &sC, MoleculeContainer &mC);
	~MixedSystem(void);

	/**
	 * Render system
	 */
	void draw();

	/**
	 * Updates system's state
	 */
	void update();

	/**
	 * Enable/Disable tracking of molecules (3rd person)
	 */
	void enable3rdPerson();

	/**
	 * Change target
	 */
	void changeTargert();

private:
	SpringContainer springContainer;
	MoleculeContainer moleculeContainer;

	/**
	 * Search through particles for collisions between
	 * system(springs) and system(molecules)
	 */
	void resolveSystemCollisions();

	/**
	 * Checks and resolves a collision
	 *
	 * @param (sphere, molecule, index to molecule sub sphere)
	 */
	void checkSpheres(Sphere &p, Molecule &m, int k);
};

#endif

