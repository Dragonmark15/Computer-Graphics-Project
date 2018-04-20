#ifndef __BOX_H__
#define __BOX_H__

#include <vector>

#include "Vector3D.h"
#include "Shape.h"
#include "Triangle.h"

class Box : public Shape {
public:
	~Box(){}
	//Box(Vector3D inputMinPt, Vector3D inputMaxPt);
	Box(Vector3D inputMinPt, Vector3D inputMaxPt, Shader* inputShader);
	Shader* getShader() {return hit.shader;}
	Vector3D getNormal() {return hit.normal;}

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit);
	bool intersect(const Ray rayIn);

private:
	Vector3D minPt, maxPt;
	std::vector<Triangle> boxTriangles;
	void calculateBoxTriangles(); //runs entirely on data from this class, no externals
};

#endif
