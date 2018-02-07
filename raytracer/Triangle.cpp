#include "Triangle.h"

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	color.set(100,100,100);
	normal = (v1 - v0).cross(v2 - v0);
}

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2 Vector3D inputColor) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	color = inputColor;
	normal = (v1 - v0).cross(v2 - v0);
}



Vector3D barCoordinates(Vector3D vectorIn) {
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
