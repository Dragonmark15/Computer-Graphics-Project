#include "Sphere.h"

Sphere::Sphere(Vector3D inputCenter, float inputRadius) {
	center = inputCenter;
	radius = inputRadius;
}

Sphere::Sphere(Vector3D inputCenter, float inputRadius, Vector3D inputColor) {
	center = inputCenter;
	radius = inputRadius;
	color = inputColor;
}

void Sphere::intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor) {
////////////////////////////////////////////
std::cout << "Inside intersect" << std::endl;
////////////////////////////////////////////
	tValue testValue = calculateT(origin, direction);
////////////////////////////////////////////
std::cout << "After CalculateT" << std::endl;
////////////////////////////////////////////
	if(testValue.t1real) {
		if(testValue.t2real && testValue.t2 > testValue.t1) {
			if(testValue.t2 > tMin && testValue.t2 < tMax) {
				tMax = testValue.t2;
				inputColor = color;
			}
		}
		else if(testValue.t1 > tMin && testValue.t1 < tMax) {
			tMax = testValue.t1;
			inputColor = color;
		}
	}
}

bool Sphere::intersect(const Vector3D origin, const Vector3D direction) {
	tValue testValue = calculateT(origin, direction);
	return testValue.t1real;
}

tValue Sphere::calculateT(const Vector3D origin, const Vector3D direction) {
	tValue returnValue;
	double A, B, C; //Represent the values of A, B, and C in the quadratic formula
	//Calculating A
	A = direction.dot(direction);
	//Calculating B
	B = direction.dot((origin-center));
	//Calculating C
	Vector3D tempVector = (origin-center);
	C = tempVector.dot(tempVector) - (radius * radius);
	//Determine the number of T values
	double discriminant = (B * B) - (A * C);
	if(discriminant > 0.001) {
		returnValue.t1real = true;
		returnValue.t2real = true;
	}
	else if(discriminant < 0.001 && discriminant > -0.001) {
		discriminant = 0; //Prevent errors if it's negative, but still in range
		returnValue.t1real = true;
		returnValue.t2real = false;
	}
	else if(discriminant < -0.001) {
		returnValue.t1real = false;
		returnValue.t2real = false;
	}
	//Calculate T values
	if(returnValue.t1real){
		returnValue.t1 = (((-1 * B) + sqrt(discriminant))/A);
	}
	if(returnValue.t2real){
		returnValue.t2 = (((-1 * B) - sqrt(discriminant))/A);
	}
	return returnValue;
}
