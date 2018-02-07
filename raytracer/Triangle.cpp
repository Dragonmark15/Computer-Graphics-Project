#include "Triangle.h"

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	color.set(100,100,100);
	normal = (v1 - v0).cross(v2 - v0);
}

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Vector3D inputColor) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	color = inputColor;
	normal = (v1 - v0).cross(v2 - v0);
}

void Triangle::intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor) {
	Vector3D Coordinates = barCoordinates(direction);
	std::cout << "Triangle data: " << std::endl
			  << "Alpha: " << Coordinates[0] << std::endl
			  << "Beta: " << Coordinates[1] << std::endl
			  << "Gamma: " << Coordinates[2] << std::endl;
	if(Coordinates[0] < 0 || Coordinates[0] > 1 ||
	   Coordinates[1] < 0 || Coordinates[1] > 1 ||
	   Coordinates[2] < 0 || Coordinates[2] > 1) {}
	else {
		float t = calculateT(origin, direction, Coordinates);
		std::cout << "T: " << t << std::endl;
		if(t > tMin && t < tMax && t != 0) {
			tMax = t;
			inputColor = color;
		}
	}
}

bool Triangle::intersect(const Vector3D origin, const Vector3D direction) {
	Vector3D Coordinates = barCoordinates(direction);
	bool intersect = true;
	if(Coordinates[0] < 0 || Coordinates[0] > 1 ||
	   Coordinates[1] < 0 || Coordinates[1] > 1 ||
	   Coordinates[2] < 0 || Coordinates[2] > 1) intersect = false;
	return intersect;
}

float Triangle::calculateT(const Vector3D origin, const Vector3D direction, const Vector3D barCoordinates) {
	//origin + t(direction) = v0 + beta(v1-v0) + gamma(v2-v0)
	//t = ((v0 + beta(v1-v0) + gamma(v2-v0)) - origin) / direction
	Vector3D rhs = v0 + (barCoordinates[1]*(v1 - v0)) + (barCoordinates[2]*(v2 - v0));
	rhs -= origin;
	float t = rhs[0] / direction[0];
	if(direction[1]*t != rhs[1] || direction[2]*t != rhs[2]) t = 0;
	return t;
}

Vector3D Triangle::barCoordinates(const Vector3D vectorIn) {
	//Calculate two side normals. No need to do normalV2, since (1-a-b)=c
	Vector3D normalV0 = (v2 - v1).cross(vectorIn - v1);
	Vector3D normalV1 = (v0 - v2).cross(vectorIn - v2);
	//
	float normalLengthSquared = (normal.length())*(normal.length());
	//Calculate alpha
	float alpha = (normal.dot(normalV0))/(normalLengthSquared);
	float beta = (normal.dot(normalV1))/(normalLengthSquared);
	Vector3D returnVector(alpha,beta,(1-(alpha+beta)));
	return returnVector;
}

