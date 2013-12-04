#ifndef ABSTRACTCONTAINER_H_
#define ABSTRACTCONTAINER_H_

#include "Renderable.h"
#include "CollisionCounter.h"

class AbstractContainer : Renderable{
public:
	AbstractContainer();
	~AbstractContainer();

	virtual void draw() =0;
	virtual void update() =0;

	virtual void saveWallCollisions() =0;
	virtual void saveBallCollisions() =0;

protected:

	CollisionCounter wallCollisions, ballCollisions;
 
};

#endif

