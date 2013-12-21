#ifndef ABSTRACTCONTAINER_H_
#define ABSTRACTCONTAINER_H_

#include "Renderable.h"
#include "CollisionCounter.h"
#include "Camera3rd.h"
#include "Collision.h"

/**
 * Defines common methods for a container
 */
class AbstractContainer : public Renderable{
public:
	/**
	 * Default constructor
	 */
	AbstractContainer();

	/**
	 * @param cm Collision mode (only for particle system)
	 */
	AbstractContainer(bool cm);
	virtual ~AbstractContainer();

	/**
	 * Defines how to render
	 */
	virtual void draw() =0;

	/**
	 * Defines how to update state (idle)
	 */
	virtual void update() =0;

	/**
	 * Saves wall collision data to matlab dat format
	 */
	virtual void saveWallCollisions();

	/**
	* Saves ball collision data to matlab dat format
	*/
	virtual void saveBallCollisions();

	/**
	 * Draws histogram of wall collisions
	 */
	virtual void drawWallCollisions();

	/**
	 * Draws histogram of ball collisions
	 */
	virtual void drawBallCollisions();

	/**
	 * Enable/Disable 3rd person camera
	 */
	virtual void enable3rdPerson() =0;

	/**
	 * Changes target of the camera
	 */
	virtual void changeTargert() =0;

	/**
	 * Changes from real mode to false mode
	 * (only for particle simulation)
	 */
	virtual void changeCollisionMode();

	/**
	 * Clears histogram data (wall and ball)
	 */
	virtual void clearCollisions();

	/**
	 * True if thirdPerson else false
	 */
	virtual bool getCameraMode();

	/**
	 * Get target index
	 */
	virtual int getTargetIndex();

	/**
	 * True for real mode else false
	 */
	virtual bool getCollisionMode();

	/**
	 * Accessor
	 */
	virtual CollisionCounter &getWallCollisionCounter();

	/**
	 * Accessor
	 */
	virtual CollisionCounter &getBallCollisionCounter();
	

protected:

	/**
	 * For histogram data
	 */
	CollisionCounter wallCollisions, ballCollisions;

	/**
	 * For collision check and handling
	 */
	Collision collision;

	/**
	 * 3rd person camera parameters
	 */
	Camera3rd camera;
	bool thirdPerson;
	unsigned int target;

	/**
	 * Real mode or false mode
	 */
	bool collisionMode;
 
};

#endif

