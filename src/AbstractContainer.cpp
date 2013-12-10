#include "AbstractContainer.h"


AbstractContainer::AbstractContainer(void){ 
	wallCollisions.setName("Wall");
	ballCollisions.setName("Ball");

	camera = Camera3rd(OFFSET_X, OFFSET_Y, OFFSET_Z);
	thirdPerson = false;
	target = 0;
}


AbstractContainer::~AbstractContainer(void){

}
