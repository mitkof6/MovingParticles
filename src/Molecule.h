#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <vector>
#include <cmath>

#include "Renderable.h"
#include "Constants.h"
#include "RigidBody.h"
#include "Math/Vectors.h"
#include "Math/Matrices.h"
#include "Math/Quaternion.h"

#include "GL/glut.h"

#define PI 3.14

using namespace std;

/**
 * Representation of molecule (visualization and physics)
 */
class Molecule : public Renderable, public RigidBody{

public:
	/**
	 * Constructs a symmetric molecules
	 *
	 * @param # of sub spheres
	 */
	Molecule(int n);
	~Molecule(void);

	/**
	 * Render molecule
	 */
	void draw();

	/**
	 * Updates position and orientation
	 */
	void update();

	/**
	 * Bounding sphere radius (for fast check)
	 */
	float getMaxRadius();

	/**
	 * Sub molecule count
	 */
	int getMoleculeCount();

	/**
	 * Displacement of ith sub sphere from mass center
	 *
	 * @param (index)
	 */
	Vector3 getDisplacement(int i);

	/**
	 * Get radius of ith sub sphere
	 *
	 * @param (index)
	 */
	float getRadius(int i);

	/**
	 * Changes color of ith sub molecule (debugging)
	 */
	void setColor(int i, float r, float g, float b);

private:
	/**
	 * Sub spheres' radius, mass
	 */
	vector<float> radius, masses;

	/**
	 * Displacement from mass center and collor
	 */
	vector<Vector3> displacement, dis, color;

	/**
	 * Bounding sphere radius
	 */
	float maxRadius;

	/**
	 * Updates orientation based on quaternion rotation.
	 * Also updates inertia, inertiaInv and displacements
	 */
	void updateOrientation();

	/**
	 * Generates random number between [min-max]
	 *
	 * @param (min, max)
	 */
	float randMM(float min, float max);
};

#endif
