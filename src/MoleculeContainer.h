#ifndef MOLECULECONTAINER_H_
#define	MOLECULECONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "Molecule.h"
#include "Wall.h"

using namespace std;

class MoleculeContainer : public AbstractContainer{
public:
	MoleculeContainer(bool collisionMode);
	~MoleculeContainer(void);

	void add(Molecule &m);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();

private:
	vector<Molecule> molecules;

	void findWallCollisions();
	bool possibleCollision(Molecule &m, Wall &w);
	void investigatePossibleCollision(Molecule &m, Wall &wall);
	bool checkForCollision(
		Molecule &m, const Vector3 &pos, float radius, 
		Wall &wallDir);

	void findMoleculeMoleculeCollisions();
	bool possibleCollision(Molecule &p, Molecule &q);
	void investigatePossibleCollision(Molecule &p, Molecule &q);
	bool checkForCollision(
		Molecule &p, const Vector3 &pPos, float pR,
		Molecule &q, const Vector3 &qPos, float qR);

	void calculateCollisionPoint(
		const Vector3 &p1, float r1,
		const Vector3 &p2, float r2,
		Vector3 &cp, Vector3 &cn);

	
};

#endif

