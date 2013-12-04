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
		Wall temp;
		if(checkForCollision(molecules[i], temp)){

			wallCollisions.incCounter();
			wallCollisions.registerEvent();

			molecules[i].collisionHandler(temp.getWallDirection());
		}
	}
}

bool MoleculeContainer::checkForCollision(Molecule &m, Wall &w){
	
	Vector3D pos = m.getCenter();
	float r = m.getMaxRadius();

	if(pos.x-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.x-r);
		m.setCenter(pos+Vector3D(dis, 0, 0));

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.x+r);
		m.setCenter(pos+Vector3D(dis, 0, 0));

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.y-r);
		m.setCenter(pos+Vector3D(0, dis, 0));

		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.y+r);
		m.setCenter(pos+Vector3D(0, dis, 0));

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.z-r);
		m.setCenter(pos+Vector3D(0, 0, dis));

		w = Wall(WALL_NEAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.z+r);
		m.setCenter(pos+Vector3D(0, 0, dis));

		w = Wall(WALL_FAR);
		
	}else{
		return false;
	}

	return true;
}
