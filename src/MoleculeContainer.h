#ifndef MOLECULECONTAINER_H_
#define	MOLECULECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Molecule.h"
#include "Wall.h"

using namespace std;

/**
 * Used for dumping (make stable)
 */
#define GAIN 1.0

/**
 *Molecule container contains a vector of molecules
 *and handles collisions with wall and between molecules
 */
class MoleculeContainer : public AbstractContainer{
public:
	vector<Molecule> molecules;

	/**
	 * Default constructor
	 */
	MoleculeContainer();
	~MoleculeContainer(void);

	/**
	 * Adds a molecule to system
	 */
	void add(Molecule m);

	/**
	 * Render all molecules
	 */
	void draw();

	/**
	 * Update molecules' states
	 */
	void update();

	void enable3rdPerson();
	void changeTargert();


private:
	/**
	 * Scan for bounding sphere and wall collision.
	 * If bounding sphere collides with wall then
	 * calls invesigatePossibleWallCollision
	 */
	void findWallCollisions();

	/**
	 * Checks every sub sphere with wall
	 */
	void investigatePossibleWallCollision(Molecule &m, Wall &wall);

	/**
	 * Scan between bounding spheres. If collision exists
	 * then calls for investigation
	 */
	void findMoleculeCollisions();

	/**
	 * Checks every sub sphere between two molecules
	 */
	void investigatePossibleMoleculeCollision(Molecule &p, Molecule &q);

};

#endif

