#ifndef MOLECULECONTAINER_H_
#define	MOLECULECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Molecule.h"
#include "Wall.h"

using namespace std;

class MoleculeContainer : public AbstractContainer{
public:
	MoleculeContainer();
	~MoleculeContainer(void);

	void add(Molecule &m);

	void draw();
	void update();

	void saveWallCollisions();
	void saveBallCollisions();

private:
	vector<Molecule> molecules;

	void findWallCollisions();
	bool possibleCollision(Molecule &m, Wall &w);
	void investigatePossibleCollision(Molecule &m, Wall wall);
	bool checkForCollision(
		Molecule &m, Vector3D pos, float radius, 
		Wall wallDir,
		Vector3D &cp);

	void findMoleculeMoleculeCollisions();
	bool possibleCollision(Molecule &p, Molecule &q);
	void investigatePossibleCollision(Molecule &p, Molecule &q);
	bool checkForCollision(
		Molecule &p, Vector3D pPos, float pR,
		Molecule &q, Vector3D qPos, float qR, Vector3D &cp);

	
};

#endif

