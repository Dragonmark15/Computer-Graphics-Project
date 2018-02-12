#include "Triangle.h"

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	hit.color.set(100,100,100);
	hit.normal = (v1 - v0).cross(v2 - v0);
}

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Vector3D inputColor) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	hit.color = inputColor;
	hit.normal = (v1 - v0).cross(v2 - v0);
}

void Triangle::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	float t = calculateT(rayIn);
	if (t > tMin && t < tMax) {
		tMax = t;
		inputHit = hit;
	}
}

bool Triangle::intersect(const Ray rayIn) {
	return (calculateT(rayIn) != 0);
}

float Triangle::calculateT(const Ray rayIn) {
	float t; //If T is returned as 0, it doesn't intersect with the triangle
	float distFromZero = hit.normal.dot(v0);
	float tDenominator = hit.normal.dot(rayIn.direction);
	if(tDenominator > -0.000001 && tDenominator < 0.000001) t = 0; //Zero test. If equal to zero, triangle is perpendicular to the ray
	else {
		//Calculate T
		float tNumerator = hit.normal.dot(rayIn.origin) + distFromZero;
		float t = (-1 * tNumerator) / (-1 * tDenominator); //TODO: Change this to be negative only when the normal faces the camera. For oneTriangle and threeTriangle, this works fine for now
		//Determine in p(t) is in the triangle
		Vector3D P = rayIn.origin + (t * rayIn.direction); //The point on the plane and the ray
		//Calculate barycentric coordinates using triangle area method
		float areaAll = triangleArea(v0,v1,v2);
		float areaA = triangleArea(v2,v0,P);
		float areaB = triangleArea(v0,v1,P);
		float areaC = triangleArea(v1,v2,P);
		
		float alpha = areaA/areaAll;
		float beta = areaB/areaAll;
		float gamma = areaC/areaAll;

		if ((alpha+beta+gamma) > 0.99999 && (alpha+beta+gamma) < 1.00001 &&
			alpha > 0 && alpha < 1 &&
			beta > 0 && beta < 1 &&
			gamma > 0 && gamma < 1) {}
		else t = 0;
		return t;
		
	} 
}

float Triangle::triangleArea(const Vector3D a, const Vector3D b, const Vector3D c) {
	Vector3D u = b - a;
	Vector3D v = c - a;
	return (float)(0.5 * u.cross(v).length());
}

