#ifndef GRID_H_
#define GRID_H_

#include <vector>

#include "Sphere.h"
#include "Renderable.h"
#include "Math/Vectors.h"

#include "Constants.h"

#include "GL/glut.h"

using namespace std;

class Grid : public Renderable{
public:
	Grid(int n, int m);
	~Grid(void);

	void draw();
	void update();

private:
	vector<vector<Sphere>> grid;
	
	int N, M;
	float restLengthX, restLengthY;
	float k;
	float b;

	/**
	 * Used to generate random numbers between [min-max]
	 *
	 * @param (min, max)
	 */
	float randMM(float min, float max);
};

#endif

