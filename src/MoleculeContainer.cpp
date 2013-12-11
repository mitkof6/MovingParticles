#include "MoleculeContainer.h"


MoleculeContainer::MoleculeContainer(): AbstractContainer(){

}


MoleculeContainer::~MoleculeContainer(void){

}

void MoleculeContainer::add(Molecule &m){
	molecules.push_back(m);
}

void MoleculeContainer::draw(){
	if(thirdPerson){
		camera.draw();
	}

	for(unsigned i = 0;i<molecules.size();i++){
		molecules[i].draw();
	}
}

void MoleculeContainer::update(){
	wallCollisions.incTime();
	ballCollisions.incTime();

	if(thirdPerson){
		camera.update();
	}

	for(unsigned i = 0;i<molecules.size();i++){
		molecules[i].update();
	}

	findWallCollisions();

	findMoleculeMoleculeCollisions();
}

void MoleculeContainer::enable3rdPerson(){
	thirdPerson = !thirdPerson;
	camera.lock(molecules[target].getMassCenter());
}

void MoleculeContainer::changeTargert(){
	target++;
	if(target==molecules.size()){
		target = 0;
	}
	camera.lock(molecules[target].getMassCenter());

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
	
	Vector3 pos = m.getMassCenter();
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

void MoleculeContainer::investigatePossibleCollision(Molecule &m, Wall &wall){
	for(int j = 0;j<m.getMoleculeCount();j++){//per molecule check
		
		if(checkForCollision(
			m, m.getMassCenter()+m.getDisplacement(j), m.getRadius(j),
			wall)){

			//TODO collision point
			/*
			Vector3 cp, cn;
			calculateCollisionPoint(
				m.getMassCenter()+m.getDisplacement(j), m.getRadius(j),
				m.getMassCenter()+m.getDisplacement(j)+wall.getWallDirection()*m.getRadius(j), 0,
				cp, cn);
			
			m.applyForce(m, cp, cn);
			*/

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
	Molecule &m, const Vector3 &pos, float radius,
	Wall &wallDir){

	switch(wallDir.getWall()){
		
		case WALL_LEFT:
			if(pos.x-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.x-radius);
				m.setMassCenter(m.getMassCenter()+Vector3(dis, 0, 0));

				return true;
			}else{
				return false;
			}
		case WALL_RIGHT:
			if(pos.x+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.x+radius);
				m.setMassCenter(m.getMassCenter()+Vector3(dis, 0, 0));

				return true;
			}else{
				return false;
			}
		case WALL_BOTTOM:
			if(pos.y-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.y-radius);
				m.setMassCenter(m.getMassCenter()+Vector3(0, dis, 0));
				
				return true;
			}else{
				return false;
			}
		case WALL_TOP:
			if(pos.y+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.y+radius);
				m.setMassCenter(m.getMassCenter()+Vector3(0, dis, 0));

				return true;
			}else{
				return false;
			}
		case WALL_NEAR :
			if(pos.z-radius	<=-BOX_SIZE/2.0f){
				//correction
				float dis = -BOX_SIZE/2.0f-(pos.z-radius);
				m.setMassCenter(m.getMassCenter()+Vector3(0, 0, dis));

				return true;
			}else{
				
				return false;
			}
		case WALL_FAR:
			if(pos.z+radius	>= BOX_SIZE/2.0f){
				//correction
				float dis = BOX_SIZE/2.0f-(pos.z+radius);
				m.setMassCenter(m.getMassCenter()+Vector3(0, 0, dis));

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
	Vector3 displacement = p.getMassCenter()-q.getMassCenter();

	float r = (p.getMaxRadius()+q.getMaxRadius());

	if(displacement.lengthSq()<r*r){
		return true;
	}else{
		return false;
	}

}

void MoleculeContainer::investigatePossibleCollision(Molecule &p, Molecule &q){
	
	for(int i = 0;i<p.getMoleculeCount();i++){
		for(int j = 0;j<q.getMoleculeCount();j++){
			if(checkForCollision(
				p, p.getMassCenter()+p.getDisplacement(i), p.getRadius(i),
				q, q.getMassCenter()+q.getDisplacement(j), q.getRadius(j))){

				//TODO collision point
				
				//handle collision
				p.collisionHandler(q);

				ballCollisions.incCounter();
				ballCollisions.registerEvent();
			}
		}
	}
}

bool MoleculeContainer::checkForCollision(
	Molecule &p, const Vector3 &pPos, float pR,
	Molecule &q, const Vector3 &qPos, float qR){

	Vector3 displacement = pPos-qPos;

	float r = pR+qR;

	if(displacement.lengthSq()<r*r){
		//correction
		Vector3 n = displacement.normalize();
		float dr = (pR+qR-displacement.length())/2;
		p.setMassCenter(p.getMassCenter()+n*dr);

		return true;
	}else{
		return false;
	}
}

void MoleculeContainer::calculateCollisionPoint(
	const Vector3 &p1, float r1,
	const Vector3 &p2, float r2,
	Vector3 &cp, Vector3 &cn){

	float t = r1/(r1+r2);

	cp = p1+(p2-p1)*t;
	cn = (p2-p1).normalize()*(-1);
}
