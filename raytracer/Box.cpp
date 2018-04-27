#include "Box.h"
/*
Box::Box(Vector3D inputMinPt, Vector3D inputMaxPt) {
	minPt = inputMinPt;
	maxPt = inputMaxPt;
	Vector3D tempVector(100,100,100);
	Shader* defaultShader = new Shader(tempVector);
	hit.shader = defaultShader;
	calculateBoxTriangles();
}
*/
Box::Box(Vector3D inputMinPt, Vector3D inputMaxPt, Shader* inputShader) {
	minPt = inputMinPt;
	maxPt = inputMaxPt;
	hit.shader = inputShader;
	calculateBoxTriangles();
}

void Box::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	for(int i = 0; i < boxTriangles.size() ; i++) {
		boxTriangles[i].intersect(rayIn, tMin, tMax, inputHit);
	}
}

bool Box::intersect(const Ray rayIn) {
	bool hit = false;
	for(int i = 0; i < boxTriangles.size() ; i++) {
		hit = boxTriangles[i].intersect(rayIn);
		if (hit) break;
	}
	return hit;
}

void Box::calculateBoxTriangles() {
	//Set the points for easy reference
	Vector3D A(minPt[0],maxPt[1],minPt[2]);
	Vector3D B(maxPt[0],maxPt[1],minPt[2]);
	Vector3D C(minPt[0],maxPt[1],maxPt[2]);
	Vector3D D = maxPt;
	Vector3D E = minPt;
	Vector3D F(maxPt[0],minPt[1],minPt[2]);
	Vector3D G(minPt[0],minPt[1],maxPt[2]);
	Vector3D H(maxPt[0],minPt[1],maxPt[2]);

	//Create the triangles. The sides listed don't matter, only used as a reference
	//Top of triangle
	boxTriangles.push_back(Triangle(C,B,A,hit.shader)); //Triangle 0
	boxTriangles.push_back(Triangle(C,D,B,hit.shader)); //Triangle 1
	//Back
	boxTriangles.push_back(Triangle(E,B,A,hit.shader)); //Triangle 2
	boxTriangles.push_back(Triangle(E,F,B,hit.shader)); //Triangle 3
	//Left
	boxTriangles.push_back(Triangle(G,E,A,hit.shader)); //Triangle 4
	boxTriangles.push_back(Triangle(G,A,C,hit.shader)); //Triangle 5
	//Right
	boxTriangles.push_back(Triangle(H,F,B,hit.shader)); //Triangle 6
	boxTriangles.push_back(Triangle(H,B,D,hit.shader)); //Triangle 7
	//Front
	boxTriangles.push_back(Triangle(G,D,C,hit.shader)); //Triangle 8
	boxTriangles.push_back(Triangle(G,H,D,hit.shader)); //Triangle 9
	//Bottom
	boxTriangles.push_back(Triangle(G,F,E,hit.shader)); //Triangle 10
	boxTriangles.push_back(Triangle(G,H,F,hit.shader)); //Triangle 11
}
