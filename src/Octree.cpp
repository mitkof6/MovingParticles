#include "Octree.h"
#include <iostream>

Octree::Octree(Vector3D c1, Vector3D c2, int d){
	corner1 = c1;
	corner2 = c2;
	center = (c1+c2)/2;
	numParticles = 0;
	depth = d;
	hasChildren = false;
}

Octree::~Octree(void){

	if(hasChildren){
		destroyChildren();
	}
}

void Octree::add(Particle p){
	numParticles++;
	if(!hasChildren &&
		depth<MAX_OCTREE_DEPTH &&
		numParticles>MAX_BALLS_PER_OCTREE){
		
		createChildren();
	}

	if(hasChildren){
		fileParticle(p, true);
	}else{
		particles.push_back(p);
	}
}

void Octree::fileParticle(Particle p, bool add){

	Vector3D pos = p.getPosition();
	float r = p.getRadius();

	for(int x = 0;x<2;x++){

		if (x == 0) {
			if (pos.x - r > center.x) {
				continue;
			}
		}else if (pos.x + r < center.x) {
			continue;
		}

		for(int y = 0;y < 2;y++) {
			if (y == 0) {
				if (pos.y - r > center.y) {
					continue;
				}
			}else if (pos.y + r < center.y) {
				continue;
			}
					
			for(int z = 0; z < 2; z++) {
				if (z == 0) {
					if (pos.z - r > center.z) {
						continue;
					}
				}else if (pos.z + r < center.z) {
					continue;
				}
						
				//add or remove	
				if (add) {
					children[x][y][z]->add(p);
				}else {
					children[x][y][z]->remove(p);
				}
			}
		}
	}
}

void Octree::remove(Particle p){
	numParticles--;
	if (hasChildren && numParticles < MIN_BALLS_PER_OCTREE){
		destroyChildren();
	}
			
	if (hasChildren) {
		fileParticle(p, false);
	}
	else {
		for(unsigned i = 0;i<particles.size();i++){
			if(particles[i].getPosition().equals(p.getPosition())){
				particles.erase(particles.begin()+i);
			}
		}
	}
		
}

void Octree::destroyChildren() {

	collectParticles(particles);
			
	for(int x = 0; x < 2; x++) {
		for(int y = 0; y < 2; y++) {
			for(int z = 0; z < 2; z++) {
				delete children[x][y][z];
			}
		}
	}
			
	hasChildren = false;
}

void Octree::collectParticles(vector<Particle> &ps) {
	if (hasChildren) {
		for(int x = 0; x < 2; x++) {
			for(int y = 0; y < 2; y++) {
				for(int z = 0; z < 2; z++) {
					children[x][y][z]->collectParticles(ps);
				}
			}
		}
	}else {
		for(unsigned i = 0;i<particles.size();i++){
			ps.push_back(particles[i]);
		}
	}
}

void Octree::createChildren(){
	for(int x = 0; x < 2; x++) {
		float minX;
		float maxX;
		if (x == 0) {
			minX = corner1.x;
			maxX = center.x;
		}else {
			minX = center.x;
			maxX = corner2.x;
		}
				
		for(int y = 0; y < 2; y++) {
			float minY;
			float maxY;
			if (y == 0) {
				minY = corner1.y;
				maxY = center.y;
			}else {
				minY = center.y;
				maxY = corner2.y;
			}
					
			for(int z = 0; z < 2; z++) {
				float minZ;
				float maxZ;
				if (z == 0) {
					minZ = corner1.z;
					maxZ = center.z;
				}else {
					minZ = center.z;
					maxZ = corner2.z;
				}
						
				children[x][y][z] = new Octree(
					Vector3D(minX, minY, minZ),
					Vector3D(maxX, maxY, maxZ),
					depth + 1);
			}
		}
	}
			
	//Remove all balls from "balls" and add them to the new children
	for(unsigned i = 0;i<particles.size();i++) {
		fileParticle(particles[i], true);
	}
	particles.clear();
			
	hasChildren = true;
}

void Octree::findWallCollisions(vector<ParticleWallContainer> &container){
	checkWall(container, WALL_LEFT, 'x', 0);
	checkWall(container, WALL_RIGHT, 'x', 1);
	checkWall(container, WALL_BOTTOM, 'y', 0);
	checkWall(container, WALL_TOP, 'y', 1);
	checkWall(container, WALL_FAR, 'z', 0);
	checkWall(container, WALL_NEAR, 'z', 1);
}


void Octree::checkWall(vector<ParticleWallContainer> &container, Wall w, char coord, int dir) {
	if (hasChildren) {
		//Recursively call potentialBallWallCollisions on the correct
		//half of the children (e.g. if w is WALL_TOP, call it on
		//children above centerY)
		for(int dir2 = 0; dir2 < 2; dir2++) {
			for(int dir3 = 0; dir3 < 2; dir3++) {
				Octree *child;
				switch (coord) {
					case 'x':
						child = children[dir][dir2][dir3];
						break;
					case 'y':
						child = children[dir2][dir][dir3];
						break;
					case 'z':
						child = children[dir2][dir3][dir];
						break;
				}
						
				child->checkWall(container, w, coord, dir);
			}
		}
	}else {
		//Add (ball, w) for all balls in this
		for(unsigned i = 0;i<particles.size();i++) {
			ParticleWallContainer cont(&particles[i], w);
			container.push_back(cont);
		}
	}
}

void Octree::draw(){
	if(hasChildren){
		for(int x = 0;x<2;x++){
			for(int y = 0;y<2;y++){
				for(int z = 0;z<2;z++){
					children[x][y][z]->draw();
				}
			}
		}
	}else{
		for(unsigned i = 0;i<particles.size();i++){
			particles[i].draw();
		}
	}
}

void Octree::update(){
	if(hasChildren){
		for(int x = 0;x<2;x++){
			for(int y = 0;y<2;y++){
				for(int z = 0;z<2;z++){
					children[x][y][z]->update();
				}
			}
		}
	}else{

		handleWallCollision();

		handleParticlePairCollision();

		for(unsigned i = 0;i<particles.size();i++){
			Particle p =  particles[i];
			remove(p);
			p.update();
			add(p);
		}

		
	}
}

void Octree::handleWallCollision(){
	vector<ParticleWallContainer> container;

	findWallCollisions(container);

	for(unsigned i = 0;i<container.size();i++){

		if(container[i].checkCollision()){
			container[i].getParticle()->collisionHandler(
				container[i].getWall().getWallDirection());
		}
	}
}

void Octree::findParticleCollisions(vector<ParticlePairContainer> &container){
	if (hasChildren) {
		for(int x = 0; x < 2; x++) {
			for(int y = 0; y < 2; y++) {
				for(int z = 0; z < 2; z++) {
					children[x][y][z]->
						findParticleCollisions(container);
				}
			}
		}
	}else {
		//Add all pairs (ball1, ball2) from balls
		for(unsigned i = 0;i<particles.size();i++){
			Particle *p1 = &particles[i];
			for(unsigned j = 0;j<particles.size();j++) {
				Particle *p2 = &particles[j];
				//This test makes sure that we only add each pair once
				if (i < j) {
					container.push_back(ParticlePairContainer(p1, p2));
				}
			}
		}
	}
}

void Octree::handleParticlePairCollision(){

	vector<ParticlePairContainer> container;

	findParticleCollisions(container);

	for(unsigned i = 0;i<container.size();i++){

		if(container[i].checkCollision()){

			container[i].getP1()->collisionHandler(*container[i].getP2());
			container[i].getP1()->setColor(1.0, 1.0, 1.0);
			container[i].getP2()->collisionHandler(*container[i].getP1());
			container[i].getP2()->setColor(1.0, 1.0, 1.0);

		}
	}
}
