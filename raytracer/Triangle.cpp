#include "Triangle.h"

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	Vector3D tempVector(100,100,100);
	Shader* defaultShader = new Shader(tempVector);
	hit.shader = defaultShader;
	hit.normal = (v1 - v0).cross(v2 - v0);
	hit.normal.normalize();
}

Triangle::Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Shader* inputShader) {
	v0 = inputv0;
	v1 = inputv1;
	v2 = inputv2;
	hit.shader = inputShader;
	hit.normal = (v1 - v0).cross(v2 - v0);
	hit.normal.normalize();
}

void Triangle::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	float t = calculateT(rayIn);
	if (t > tMin && t < tMax) {
		tMax = t;
		Vector3D pointOfImpact = rayIn.origin + (tMax * rayIn.direction);
		hit.point = pointOfImpact;
		inputHit = hit;
	}
}

bool Triangle::intersect(const Ray rayIn) {
	return (calculateT(rayIn) != 0);
}
/*
float Triangle::calculateT(const Ray rayIn) {
	float t; //If T is returned as 0, it doesn't intersect with the triangle
	float distFromZero = hit.normal.dot(v0);
	float tDenominator = hit.normal.dot(rayIn.direction);
	if(tDenominator > -0.000001 && tDenominator < 0.000001) t = 0; //Zero test. If equal to zero, triangle is perpendicular to the ray
	else {
		//Calculate T
		float tNumerator = hit.normal.dot(rayIn.origin) + distFromZero;
		float t = tNumerator / tDenominator;
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
*/
float Triangle::calculateT(const Ray rayIn) {
	//Calculate barycentric coordinates through matrix method on page 79
	float a,b,c,d,e,f,g,h,i,j,k,l,M,beta,gamma,t;
	a =	v0[0] - v1[0];
	b =	v0[1] - v1[1];
	c =	v0[2] - v1[2];
	d =	v0[0] - v2[0];
	e =	v0[1] - v2[1];
	f =	v0[2] - v2[2];
	g = rayIn.direction[0];
	h = rayIn.direction[1];
	i = rayIn.direction[2];
	j =	v0[0] - rayIn.origin[0];
	k =	v0[1] - rayIn.origin[1];
	l =	v0[2] - rayIn.origin[2];
	//Calculate common values
	float ei_hf = (e * i) - (h * f);
	float gf_di = (g * f) - (d * i);
	float dh_eg = (d * h) - (e * g);
	float ak_jb = (a * k) - (j * b);
	float jc_al = (j * c) - (a * l);
	float bl_kc = (b * l) - (k * c);
	//Calculate M, beta, gamma, and t
	M = (a * ei_hf) + (b * gf_di) + (c * dh_eg);
	beta = ((j * ei_hf) + (k * gf_di) + (l * dh_eg)) / M;
	gamma = ((i * ak_jb) + (h * jc_al) + (g * bl_kc)) / M;
	t = -1 * ((f * ak_jb) + (e * jc_al) + (d * bl_kc)) / M;
	if(gamma < 0 || gamma > 1)  return 0;
	if(beta < 0 || beta > (1 - gamma)) return 0;
	return t;
}


float Triangle::triangleArea(const Vector3D a, const Vector3D b, const Vector3D c) {
	Vector3D u = b - a;
	Vector3D v = c - a;
	return (float)(0.5 * u.cross(v).length());
}

