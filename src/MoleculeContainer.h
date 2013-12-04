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
	bool checkForCollision(Molecule &m, Wall &w);

	bool checkForCollision(
		Vector3D pos, float radius, Wall wallDir,
		Molecule &m, Vector3D col);
};

#endif

