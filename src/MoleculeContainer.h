#ifndef MOLECULECONTAINER_H_
#define	MOLECULECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Molecule.h"
#include "Wall.h"

using namespace std;

#define GAIN 1.0

class MoleculeContainer : public AbstractContainer{
public:
	vector<Molecule> molecules;

	MoleculeContainer();
	~MoleculeContainer(void);

	void add(Molecule m);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();


private:
	void findWallCollisions();
	void investigatePossibleWallCollision(Molecule &m, Wall &wall);

	void findMoleculeCollisions();
	void investigatePossibleMoleculeCollision(Molecule &p, Molecule &q);

	void calculateCollisionPoint(
		const Vector3 &p1, float r1,
		const Vector3 &p2, float r2,
		Vector3 &cp, Vector3 &cn);

	
};

#endif

