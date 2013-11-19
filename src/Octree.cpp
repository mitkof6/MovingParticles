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

void Octree::add(Particle &p){
	numParticles++;
	if(!hasChildren &&
		depth<MAX_OCTREE_DEPTH &&
		numParticles>MAX_BALLS_PER_OCTREE){
		
		createChildren();
	}

	if(hasChildren){
		fileParticle(p, p.getPosition(), true);
	}else{
		particles.push_back(p);
		//std::cout<<numParticles<<" push\n";
	}
}

void Octree::fileParticle(Particle &p, Vector3D pos, bool add){

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
					//std::cout<<x<<", "<<y<<", "<<z<<"\n";
				}else {
					children[x][y][z]->remove(p, pos);
				}
			}
		}
	}
}

void Octree::remove(Particle p, Vector3D pos){
	numParticles--;
	if (hasChildren && numParticles < MIN_BALLS_PER_OCTREE){
		destroyChildren();
	}
			
	if (hasChildren) {
		fileParticle(p, pos, false);
	}
	else {
		for(unsigned i = 0;i<particles.size();i++){
			if(particles[i].getPosition().equals(pos)){
				particles.erase(particles.begin()+i);//problem ?
			}
		}
	}
		
}

void Octree::destroyChildren() {
	//Move all balls in descendants of this to the "balls" set
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
		for(vector<Particle>::iterator it = particles.begin(); it != particles.end();it++) {
			Particle p = *it;
			ps.push_back(p);
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
	for(vector<Particle>::iterator it = particles.begin(); it != particles.end();it++) {
		Particle p = *it;
		fileParticle(p, p.getPosition(), true);
	}
	particles.clear();
			
	hasChildren = true;
}
