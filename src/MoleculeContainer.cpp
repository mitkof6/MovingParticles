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

	findMoleculeMoleculeCollisions();
}

void MoleculeContainer::saveWallCollisions(){

}

void MoleculeContainer::saveBallCollisions(){

}

void MoleculeContainer::findWallCollisions(){
	for(unsigned i = 0;i<molecules.size();i++){
		Wall wall;
		if(possibleCollision(molecules[i], wall)){//possible collision check

			investigatePossibleCollision(molecules[i], wall);
			
		}
	}
}

bool MoleculeContainer::possibleCollision(Molecule &m, Wall &w){
	
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

void MoleculeContainer::investigatePossibleCollision(Molecule &m, Wall wall){
	for(int j = 0;j<m.getMoleculeCount();j++){//per molecule check
		Vector3D collisionPoint;
		if(checkForCollision(
			m, m.getCenter()+m.getDisplacement(j), m.getRadius(j),
			wall,
			collisionPoint)){

			//TODO collision point

			//handle collision
			m.collisionHandler(wall.getWallDirection());
					
			//counter
			wallCollisions.incCounter();
			wallCollisions.registerEvent();
					
			break;

		}
	}
}

bool MoleculeContainer::checkForCollision(
	Molecule &m, Vector3D pos, float radius,
	Wall wallDir, 
	Vector3D &col){

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

void MoleculeContainer::findMoleculeMoleculeCollisions(){
	
	for(unsigned i = 0;i<molecules.size();i++){

		for(unsigned j = 0;j<molecules.size();j++){
			
			if(i<j){
				if(	possibleCollision(molecules[i], molecules[j])){//check for possible collision

					investigatePossibleCollision(molecules[i], molecules[j]);//per molecule check
					
				}

			}
		}
	}
}

bool MoleculeContainer::possibleCollision(Molecule &p, Molecule &q){
	Vector3D displacement = p.getCenter()-q.getCenter();

	float r = (p.getMaxRadius()+q.getMaxRadius());

	if(displacement.magnitudeSquared()<r*r){
		return true;
	}else{
		return false;
	}

}

void MoleculeContainer::investigatePossibleCollision(Molecule &p, Molecule &q){
	
	for(int i = 0;i<p.getMoleculeCount();i++){
		for(int j = 0;j<q.getMoleculeCount();j++){
			Vector3D collisionPoint;
			if(checkForCollision(
				p, p.getCenter()+p.getDisplacement(i), p.getRadius(i),
				q, q.getCenter()+q.getDisplacement(j), q.getRadius(j),
				collisionPoint)){

				//TODO collision point
				
				//handle collision
				p.collisionHandler(q);
			}
		}
	}
}

bool MoleculeContainer::checkForCollision(
	Molecule &p, Vector3D pPos, float pR,
	Molecule &q, Vector3D qPos, float qR, Vector3D &cp){

	Vector3D displacement = pPos-qPos;

	float r = pR+qR;

	if(displacement.magnitudeSquared()<r*r){
		//correction
		Vector3D n = displacement.normalize();
		float dr = (pR+qR-displacement.magnitude())/2;
		p.setCenter(p.getCenter()+n*dr);

		return true;
	}else{
		return false;
	}
}
