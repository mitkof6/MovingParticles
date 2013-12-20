#ifndef SPRINGCONTAINER_H_
#define SPRINGCONTAINER_H_

#include <vector>

#include "ParticleContainer.h"
#include "DoubleSpring.h"
#include "Particle.h"

using namespace std;

class SpringContainer : public ParticleContainer{
public:
	SpringContainer();
	~SpringContainer(void);

	void add(DoubleSpring &ds);

	void draw();
	void update();


private:

	vector<DoubleSpring> doubleSprings;
};

#endif
