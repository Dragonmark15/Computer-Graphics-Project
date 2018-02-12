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

/*
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
*/

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
/*
void Triangle::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	Vector3D Coordinates = barCoordinates(rayIn);
	if(Coordinates[0] > tMin && Coordinates[0] < tMax && //t is between tMin and tMax
	   Coordinates[2] > 0 && Coordinates[2] < 1 && //gamma test
	   Coordinates[1] > 0 && Coordinates[1] < (1 - Coordinates[2])) { //beta test, and test everything is less than 1
		tMax = Coordinates[0];
		inputHit = hit;
		std::cout << "hit" << std::endl;
	} 
	else {

		//float t = calculateT(rayIn, Coordinates);
		//std::cout << "T: " << t << std::endl;
		//if(t > tMin && t < tMax && t != 0) {
		//	tMax = t;
		//	inputHit = hit;
		}
	}
}

bool Triangle::intersect(const Ray rayIn) {
	Vector3D Coordinates = barCoordinates(rayIn);
	bool intersect = false;
	if(Coordinates[0] > 0 && Coordinates[0] < 1000000000 && 
	   Coordinates[2] > 0 && Coordinates[2] < 1 && 
	   Coordinates[1] > 0 && Coordinates[1] < (1 - Coordinates[2])) intersect = true;
	return intersect;
}

float Triangle::calculateT(const Ray rayIn, const Vector3D barCoordinates) {
	//origin + t(direction) = v0 + beta(v1-v0) + gamma(v2-v0)
	//t = ((v0 + beta(v1-v0) + gamma(v2-v0)) - origin) / direction
	Vector3D rhs = v0 + (barCoordinates[1]*(v1 - v0)) + (barCoordinates[2]*(v2 - v0));
	//rhs -= origin;
	float t = (rhs-rayIn.origin)[0] / rayIn.direction[0];
	if(rayIn.direction[1]*t != rhs[1] || rayIn.direction[2]*t != rhs[2]) t = 0;
	return t;
}*/
/*
float Triangle::calculateT(const Vector3D origin, const Vector3D direction, const Vector3D barCoordinates) {
	//origin + t(direction) = v0 + beta(v1-v0) + gamma(v2-v0)
	//t = ((v0 + beta(v1-v0) + gamma(v2-v0)) - origin) / direction
	Vector3D rhs = v0 + (barCoordinates[1]*(v1 - v0)) + (barCoordinates[2]*(v2 - v0));
	//rhs -= origin;
	float t = (rhs-origin)[0] / direction[0];
	if(direction[1]*t != rhs[1] || direction[2]*t != rhs[2]) t = 0;
	return t;
}

Vector3D Triangle::barCoordinates(const Vector3D vectorIn) {
	//Calculate two side normals. No need to do normalV2, since (1-a-b)=c
	Vector3D normalV0 = (v2 - v1).cross(vectorIn - v1);
	Vector3D normalV1 = (v0 - v2).cross(vectorIn - v2);
	Vector3D normalV2 = (v1 - v0).cross(vectorIn - v0);
	//
	float normalLengthSquared = (normal.length())*(normal.length());
	//Calculate alpha
	float alpha = (normal.dot(normalV0))/(normalLengthSquared);
	float beta = (normal.dot(normalV1))/(normalLengthSquared);
	float gamma = (normal.dot(normalV2))/(normalLengthSquared);
	Vector3D returnVector(alpha,beta,gamma);
//	Vector3D returnVector(alpha,beta,(1-(alpha+beta)));
	return returnVector;
}
*/
/*
Vector3D Triangle::barCoordinates(const Ray rayIn) {
	float a,b,c,d,e,f,g,h,i,j,k,l,beta,gamma,t; //Based on the matrix in the textbook, pg79
	a = v0[0]-v1[0];
	b = v0[1]-v1[1];
	c = v0[2]-v1[2];
	d = v0[0]-v2[0];
	e = v0[1]-v2[1];
	f = v0[2]-v2[2];
	g = rayIn.direction[0];
	h = rayIn.direction[1];
	i = rayIn.direction[2];
	j = v0[0]-rayIn.origin[0];
	k = v0[1]-rayIn.origin[1];
	l = v0[2]-rayIn.origin[2];

	float M = (a*((e*i)-(h*f)))+(b*((g*f)-(d*i)))+(c*((d*h)-(e*g)));

	beta = (j*((e*i)-(h*f)))+(k*((g*f)-(d*i)))+(l*((d*h)-(e*g)))/M;
	gamma = (i*((a*k)-(j*b)))+(h*((j*c)-(a*l)))+(g*((b*l)-(k*c)))/M;
	t = -1*(f*((a*k)-(j*b)))+(e*((j*c)-(a*l)))+(d*((b*l)-(k*c)))/M;

	///////////////////////////////////////
	std::cout << "rayIn.direction: (" << rayIn.direction[0] << "," << rayIn.direction[1] << "," << rayIn.direction[2] << ")" << std::endl << "a: " << a << " b: " << b << " c: " << c << " d: " << d << " e: " << e << " f: " << f << " g: " << g << " h: " << h << " i: " << i << " j: " << j << " k: " << k << " l: " << l << std::endl << "M: " << M << " beta: " << beta << " gamma: " << gamma << " t: " << t << std::endl;
	///////////////////////////////////////
	Vector3D returnVector(t,beta,gamma);
	return returnVector;
}
*/

