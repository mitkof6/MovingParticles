#ifndef SPRINGCONTAINER_H_
#define SPRINGCONTAINER_H_

#include <vector>

#include "AbstractContainer.h"
#include "DoubleSpring.h"
#include "Particle.h"

using namespace std;

class SpringContainer : public AbstractContainer{
public:
	SpringContainer();
	~SpringContainer(void);

	void add(DoubleSpring ds);

	void draw();
	void update();

	void enable3rdPerson();
	void changeTargert();

private:

	vector<DoubleSpring> doubleSprings;
	vector<Particle> particles;
};

#endif
