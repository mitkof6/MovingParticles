#include "Collision.h"


Collision::Collision(void)
{
}


Collision::~Collision(void){

}


bool Collision::checkForWallCollision(Vector3 &massCenter, const Vector3 &pos, float r, Wall &w){

	if(pos.x-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.x-r);
		//p.setMassCenter(pos+Vector3(dis, 0, 0));
		massCenter = massCenter+Vector3(dis, 0, 0);

		w = Wall(WALL_LEFT);

	}else if(pos.x+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.x+r);
		//p.setMassCenter(pos+Vector3(dis, 0, 0));
		massCenter = massCenter+Vector3(dis, 0, 0);

		w = Wall(WALL_RIGHT);
		
	}else if(pos.y-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.y-r);
		//p.setMassCenter(pos+Vector3(0, dis, 0));
		massCenter = massCenter+Vector3(0, dis, 0);

		w = Wall(WALL_BOTTOM);
		
	}else if(pos.y+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.y+r);
		//p.setMassCenter(pos+Vector3(0, dis, 0));
		massCenter = massCenter+Vector3(0, dis, 0);

		w = Wall(WALL_TOP);
		
	}else if(pos.z-r<=-BOX_SIZE/2.0f){
		//correction
		float dis = -BOX_SIZE/2.0f-(pos.z-r);
		//p.setMassCenter(pos+Vector3(0, 0, dis));
		massCenter = massCenter+Vector3(0, 0, dis);

		w = Wall(WALL_FAR);
		
	}else if(pos.z+r>=BOX_SIZE/2.0f){
		//correction
		float dis = BOX_SIZE/2.0f-(pos.z+r);
		//p.setMassCenter(pos+Vector3(0, 0, dis));
		massCenter = massCenter+Vector3(0, 0, dis);

		w = Wall(WALL_NEAR);
		
	}else{
		return false;
	}

	return true;
}

bool Collision::checkForSpheresCollision(Vector3 &massCenter, const Vector3 &p, float r1, const Vector3 &q, float r2){
	Vector3 displacement = p-q;

	float r = (r1+r2);

	if(displacement.lengthSq()<r*r){
		//correction
		Vector3 displacement = p-q;
		float dr = (r1+r2-displacement.length())/2;
		Vector3 n = displacement.normalize();
		massCenter = massCenter+n*dr;

		return true;
	}else{

		return false;
	}

}
