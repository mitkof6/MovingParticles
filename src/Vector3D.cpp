#include "Vector3D.h"
#include "stdio.h"

Vector3D::Vector3D() {

}

Vector3D::Vector3D(const Vector3D &other){
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3D::Vector3D(float xx, float yy, float zz){
	x = xx;
	y = yy;
	z = zz;
}

Vector3D::~Vector3D() {

}

Vector3D Vector3D::operator +(const Vector3D &other) const{
	return Vector3D(x+other.x, y+other.y, z+other.z);
}

Vector3D Vector3D::operator -(const Vector3D &other) const{
	return Vector3D(x-other.x, y-other.y, z-other.z);
}

Vector3D Vector3D::operator *(float c) const{
	return Vector3D(c*x, c*y, c*z);
}

Vector3D Vector3D::operator /(float c) const{
	return Vector3D(x/c, y/c, z/c);
}

float Vector3D::dot(const Vector3D &other) const{
	return x*other.x+y*other.y+z*other.z;
}

Vector3D Vector3D::cross(const Vector3D &other) const{
	return Vector3D(
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x);
}

Vector3D Vector3D::normalize() const{
	float d = sqrt(x*x+y*y+z*z);
	return Vector3D(x/d, y/d, z/d);
}

void Vector3D::toString() const{
	printf("[%f, %f, %f]\n", x, y, z);
}

bool Vector3D::equals(const Vector3D &other) const{
	if(abs(x-other.x) < TOLL && 
		abs(y-other.y) < TOLL &&
		abs(z-other.z) < TOLL){
		return true;
	}else{
		return false;
	}
}

float Vector3D::magnitudeSquared() const {
	return x * x + y * y + z * z;
}

float Vector3D::magnitude() const{
	return sqrt(x*x+y*y+z*z);
}




