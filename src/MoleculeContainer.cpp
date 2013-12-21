#include "MoleculeContainer.h"


MoleculeContainer::MoleculeContainer(): AbstractContainer(){

}


MoleculeContainer::~MoleculeContainer(void){

}

void MoleculeContainer::add(Molecule m){
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

	findMoleculeCollisions();

	wallCollisions.registerEvent();
	ballCollisions.registerEvent();
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
		if(collision.checkForWallCollision(Vector3(0, 0, 0), 
			molecules[i].getMassCenter(), molecules[i].getMaxRadius(), wall)){//possible collision check
		
			investigatePossibleWallCollision(molecules[i], wall);
			
		}
	}
}

void MoleculeContainer::investigatePossibleWallCollision(Molecule &m, Wall &wall){
	for(int j = 0;j<m.getMoleculeCount();j++){//per molecule check
		
		if(collision.checkForWallCollision(
			m.getMassCenter(), (m.getMassCenter()+m.getDisplacement(j)), m.getRadius(j),
			wall)){

			//TODO collision point
			
			Vector3 cp, cn;
			collision.calculateCollisionPoint(
				m.getMassCenter()+m.getDisplacement(j), m.getRadius(j),
				m.getMassCenter()+m.getDisplacement(j)+wall.getWallDirection()*m.getRadius(j), 0,
				cp, cn);
			
			//handle collision
			collision.handleWallCollision(
				m.getMassCenter(), m.getLinearVelocity(), m.getAngularVelocity(), m.getInertiaInv(), m.getMass(),
				cp, cn);
					
			//counter
			wallCollisions.incCounter();
					
			break;

		}
	}
}

void MoleculeContainer::findMoleculeCollisions(){
	
	for(unsigned i = 0;i<molecules.size();i++){

		for(unsigned j = 0;j<molecules.size();j++){
			
			if(i<j){
				if(	collision.checkForSpheresCollision(
					Vector3(0, 0, 0), molecules[i].getMassCenter(), molecules[i].getMaxRadius(),
					molecules[j].getMassCenter(), molecules[j].getMaxRadius())){//check for possible collision

					investigatePossibleMoleculeCollision(molecules[i], molecules[j]);//per molecule check
					
				}

			}
		}
	}
}

void MoleculeContainer::investigatePossibleMoleculeCollision(Molecule &p, Molecule &q){
	
	for(int i = 0;i<p.getMoleculeCount();i++){

		for(int j = 0;j<q.getMoleculeCount();j++){
			
			if(collision.checkForSpheresCollision(
				p.getMassCenter(), p.getMassCenter()+p.getDisplacement(i), p.getRadius(i),
				q.getMassCenter()+q.getDisplacement(j), q.getRadius(j))){
				
				Vector3 cp, cn;
				collision.calculateCollisionPoint(
					p.getMassCenter()+p.getDisplacement(i), p.getRadius(i),
					q.getMassCenter()+q.getDisplacement(j), q.getRadius(j),
					cp, cn);

				//p.setColor(i, 1, 1, 1);
				//q.setColor(j, 1, 1, 1);
				//collision handler
				collision.handleSphereCollision(
					p.getMassCenter(), p.getLinearVelocity(), p.getAngularVelocity(), p.getInertiaInv(), p.getMass(),
					q.getMassCenter(), q.getLinearVelocity(), q.getAngularVelocity(), q.getInertiaInv(), q.getMass(),
					cp, cn, GAIN);

				ballCollisions.incCounter();

				//return;
			}
		}
	}
}
