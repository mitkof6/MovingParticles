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
	void investigatePossibleCollision(Molecule &m, Wall &wall);
	bool checkForCollision(
		Molecule &m, const Vector3D &pos, float radius, 
		Wall &wallDir);

	void findMoleculeMoleculeCollisions();
	bool possibleCollision(Molecule &p, Molecule &q);
	void investigatePossibleCollision(Molecule &p, Molecule &q);
	bool checkForCollision(
		Molecule &p, const Vector3D &pPos, float pR,
		Molecule &q, const Vector3D &qPos, float qR);

	void calculateCollisionPoint(
		const Vector3D &p1, float r1,
		const Vector3D &p2, float r2,
		Vector3D &cp, Vector3D &cn);

	
};

#endif

