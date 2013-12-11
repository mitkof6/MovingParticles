#ifndef ABSTRACTCONTAINER_H_
#define ABSTRACTCONTAINER_H_

#include "Renderable.h"
#include "CollisionCounter.h"
#include "Camera3rd.h"

class AbstractContainer : public Renderable{
public:
	AbstractContainer();
	~AbstractContainer();

	virtual void draw() =0;
	virtual void update() =0;

	virtual void saveWallCollisions();
	virtual void saveBallCollisions();

	virtual void drawWallCollisions();
	virtual void drawBallCollisions();

	virtual void enable3rdPerson() =0;
	virtual void changeTargert() =0;

protected:

	CollisionCounter wallCollisions, ballCollisions;

	Camera3rd camera;
	bool thirdPerson;
	int target;
 
};

#endif

