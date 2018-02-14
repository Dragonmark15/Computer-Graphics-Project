#include "Box.h"

Box::Box(Vector3D inputMinPt, Vector3D inputMaxPt) {
	minPt = inputMinPt;
	maxPt = inputMaxPt;
	hit.color.set(100,100,100);
	calculateBoxTriangles();
}

Box::Box(Vector3D inputMinPt, Vector3D inputMaxPt, Vector3D inputColor) {
	minPt = inputMinPt;
	maxPt = inputMaxPt;
	hit.color = inputColor;
	calculateBoxTriangles();
}

void Box::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	for(int i = 0; i < boxTriangles.size() ; i++) {
		boxTriangles[i].intersect(rayIn, tMin, tMax, inputHit);
	}
}

bool Box::intersect(const Ray rayIn) {
	bool hit;
	for(int i = 0; i < boxTriangles.size() ; i++) {
		hit = boxTriangles[i].intersect(rayIn);
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
	boxTriangles.push_back(Triangle(C,B,A,hit.color));
	boxTriangles.push_back(Triangle(C,D,B,hit.color));
	//Back
	boxTriangles.push_back(Triangle(E,B,A,hit.color));
	boxTriangles.push_back(Triangle(E,F,B,hit.color));
	//Left
	boxTriangles.push_back(Triangle(G,E,A,hit.color));
	boxTriangles.push_back(Triangle(G,A,C,hit.color));
	//Right
	boxTriangles.push_back(Triangle(H,F,B,hit.color));
	boxTriangles.push_back(Triangle(H,B,D,hit.color));
	//Front
	boxTriangles.push_back(Triangle(G,D,C,hit.color));
	boxTriangles.push_back(Triangle(G,H,D,hit.color));
	//Bottom
	boxTriangles.push_back(Triangle(G,F,E,hit.color));
	boxTriangles.push_back(Triangle(G,H,F,hit.color));
}
