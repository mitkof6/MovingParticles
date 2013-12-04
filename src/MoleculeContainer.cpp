#include "MoleculeContainer.h"


MoleculeContainer::MoleculeContainer(): AbstractContainer(){

}


MoleculeContainer::~MoleculeContainer(void){

}

void MoleculeContainer::add(Molecule &m){
	molecules.push_back(m);
}

void MoleculeContainer::draw(){
	for(unsigned i = 0;i<molecules.size();i++){
		molecules[i].draw();
	}
}

void MoleculeContainer::update(){
	for(unsigned i = 0;i<molecules.size();i++){
		molecules[i].update();
	}

	findWallCollisions();
}

void MoleculeContainer::saveWallCollisions(){

}

void MoleculeContainer::saveBallCollisions(){

}

void MoleculeContainer::findWallCollisions(){
	for(unsigned i = 0;i<molecules.size();i++){
		Wall wall;
		if(checkForCollision(molecules[i], wall)){//general check
			for(int j = 0;j<molecules[i].getMoleculeCount();j++){//per molecule check
				Vector3D collisionPoint;
				if(checkForCollision(
					molecules[i].getCenter()+molecules[i].getDisplacement(j),
					molecules[i].getRadius(j),
					wall, molecules[i], collisionPoint)){

					//TODO collision point

					//handle collision
					molecules[i].collisionHandler(wall.getWallDirection());
					
					//counter
					wallCollisions.incCounter();
					wallCollisions.registerEvent();
					
					break;

				}
			}
		}
	}
}

bool MoleculeContainer::checkForCollision(Molecule &m, Wall &w){
	
	Vector3D pos = m.getCenter();
	float r = m.getMaxRadius();

	if(pos.x-r<=-BOX_SIZE/2.0f){

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
	
		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){

		w = Wall(WALL_NEAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){

		w = Wall(WALL_FAR);
		
	}else{
		return false;
	}

	return true;
}

bool MoleculeContainer::checkForCollision(
	Vector3D pos, float radius, Wall wallDir, 
	Molecule &m, Vector3D col){

	switch(wallDir.getWall()){
		
		case WALL_LEFT:
			if(pos.x-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.x-radius);
				m.setCenter(m.getCenter()+Vector3D(dis, 0, 0));

				return true;
			}else{
				return false;
			}
		case WALL_RIGHT:
			if(pos.x+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.x+radius);
				m.setCenter(m.getCenter()+Vector3D(dis, 0, 0));

				return true;
			}else{
				return false;
			}
		case WALL_BOTTOM:
			if(pos.y-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.y-radius);
				m.setCenter(m.getCenter()+Vector3D(0, dis, 0));
				
				return true;
			}else{
				return false;
			}
		case WALL_TOP:
			if(pos.y+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.y+radius);
				m.setCenter(m.getCenter()+Vector3D(0, dis, 0));

				return true;
			}else{
				return false;
			}
		case WALL_NEAR :
			if(pos.z-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.z-radius);
				m.setCenter(m.getCenter()+Vector3D(0, 0, dis));

				return true;
			}else{
				
				return false;
			}
		case WALL_FAR:
			if(pos.z+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.z+radius);
				m.setCenter(m.getCenter()+Vector3D(0, 0, dis));

				return true;
			}else{
				return false;
			}
		default:
			
			return false;
	}
}