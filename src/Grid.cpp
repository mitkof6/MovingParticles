#include "Grid.h"

Grid::Grid(int n, int m){
	grid.resize(n+2);
	for(int i = 0;i<grid.size();i++){
		grid[i].resize(m+2);
		
	}

	float mass = randMM(MASS_MIN, MASS_MAX);
	float radius = mass/(MASS_MAX-MASS_MIN);

	k = 1000;
	b = 100;

	double distX = BOX_SIZE/(n+1);
	double distY = BOX_SIZE/(m+1);

	for(int i = 0;i<(n+2);i++){

		for(int j = 0;j<(m+2);j++){
			
			if(i == 0 || j ==0 || i == n+2 || j == m+2){
				grid[i][j] = Sphere(
					randMM(0, 1), randMM(0, 1), randMM(0, 1),
					i*distX, 0 , j*distY,
					0, 0, 0,
					0,
					mass);	
			}else{
				grid[i][j] = Sphere(
					randMM(0, 1), randMM(0, 1), randMM(0, 1),
					i*distX, 0, j*distY,
					randMM(MIN_VX, MAX_VX),randMM(MIN_VY, MAX_VY), randMM(MIN_VZ, MAX_VZ),
					radius,
					mass);
			}

			grid[i][j].setMatirial(
				randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), randMM(AB_MIN, AB_MAX), 1.0,
				randMM(DI_MIN, DI_MAX), randMM(DI_MIN, DI_MAX), randMM(DI_MIN, AB_MAX), 1.0,
				randMM(SP_MIN, SP_MAX), randMM(SP_MIN, SP_MAX), randMM(SP_MIN, AB_MAX), 1.0,
				randMM(SH_MIN, SH_MAX));

		}
	}

	N = n+2;
	M = m+2;

	restLengthX = distX;
	restLengthY = distY;
}


Grid::~Grid(void){
}


void Grid::draw(){
	
	glPushMatrix();
	glTranslatef(-BOX_SIZE/2, 0 , -BOX_SIZE/2);
	
	for(unsigned i = 0;i<N-1;i++){

		for(unsigned j = 0;j<M-1;j++){
			glColor3f(1, 1, 1);
			if( i == 0 && j == 0) continue;

			if(j == 0){
				glBegin(GL_LINES);
				glVertex3f(
					grid[i][j].getMassCenter().x, 
					grid[i][j].getMassCenter().y, 
					grid[i][j].getMassCenter().z);
				glVertex3f(
					grid[i][j+1].getMassCenter().x, 
					grid[i][j+1].getMassCenter().y, 
					grid[i][j+1].getMassCenter().z);
				glEnd();
			}else if(i == 0){
				
				glBegin(GL_LINES);
				glVertex3f(
					grid[i][j].getMassCenter().x, 
					grid[i][j].getMassCenter().y, 
					grid[i][j].getMassCenter().z);
				glVertex3f(
					grid[i+1][j].getMassCenter().x, 
					grid[i+1][j].getMassCenter().y, 
					grid[i+1][j].getMassCenter().z);
				glEnd();		
			}else{
				glBegin(GL_LINES);
				glVertex3f(
					grid[i][j].getMassCenter().x, 
					grid[i][j].getMassCenter().y, 
					grid[i][j].getMassCenter().z);
				glVertex3f(
					grid[i+1][j].getMassCenter().x, 
					grid[i+1][j].getMassCenter().y, 
					grid[i+1][j].getMassCenter().z);
				glEnd();

				glBegin(GL_LINES);
				glVertex3f(
					grid[i][j].getMassCenter().x, 
					grid[i][j].getMassCenter().y, 
					grid[i][j].getMassCenter().z);
				glVertex3f(
					grid[i][j+1].getMassCenter().x, 
					grid[i][j+1].getMassCenter().y, 
					grid[i][j+1].getMassCenter().z);
				glEnd();
			}
			

			grid[i][j].draw();
		}
	}
	
	

	glPopMatrix();
}

void Grid::update(){
	for(unsigned i = 1;i<N-1;i++){

		for(unsigned j = 1;j<M-1;j++){

			//gravity
			grid[i][j].applayForce(Vector3(0, -grid[i][j].getMass()*G, 0));
			
			//
			Vector3 v = grid[i][j].getMassCenter();
			Vector3 v1 = grid[i-1][j].getMassCenter();
			Vector3 v2 = grid[i][j-1].getMassCenter();
			Vector3 v3 = grid[i+1][j].getMassCenter();
			Vector3 v4 = grid[i][j+1].getMassCenter();

			float L1 = (v-v1).length();
			double stretch1 = L1 - restLengthX;

			float L2 = (v-v2).length();
			double stretch2 = L2 - restLengthY;

			float L3 = (v3-v).length();
			double stretch3 = L3 - restLengthX;

			float L4 = (v4-v).length();
			double stretch4 = L4 - restLengthY;

			Vector3 dF = Vector3(
				- k*stretch1*(v.x-v1.x)/L1 - b*v1.x 
				- k*stretch2*(v.x-v2.x)/L2 - b*v2.x 
				+ k*stretch3*(v3.x-v.x)/L3 + b*v3.x 
				+ k*stretch4*(v4.x-v.x)/L4 + b*v4.x,
				- k*stretch1*(v.y-v1.y)/L1 - b*v1.y
				- k*stretch2*(v.y-v2.y)/L2 - b*v2.y 
				+ k*stretch3*(v3.y-v.y)/L3 + b*v3.y
				+ k*stretch4*(v4.y-v.y)/L4 + b*v4.y,
				- k*stretch1*(v.z-v1.z)/L1 - b*v1.z 
				- k*stretch2*(v.z-v2.z)/L2 - b*v2.z 
				+ k*stretch3*(v3.z-v.z)/L3 + b*v3.z 
				+ k*stretch4*(v4.z-v.z)/L4 + b*v4.z);
			grid[i][j].applayForce(dF);

			//integrate
			Vector3 a = grid[i][j].getTotalForce()/grid[i][j].getMass();
			grid[i][j].setLinearVelocity(grid[i][j].getLinearVelocity()+a*dt);
			grid[i][j].update();

			grid[i][j].clearForce();
		}

	}
}

float Grid::randMM(float min, float max){
	return (min+rand()*(max-min)/RAND_MAX);
}
