#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Vector3D.h"
#include "Shape.h"
#include "Shader.h"

class Triangle : public Shape {
public:
	~Triangle(){}
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2);
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Shader inputShader);
	Shader getShader() {return hit.shader;}
	Vector3D getNormal() {return hit.normal;}

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit);
	bool intersect(const Ray rayIn);

private:
	Vector3D v0, v1, v2;
	float calculateT(const Ray rayIn);
	float triangleArea(const Vector3D a, const Vector3D b, const Vector3D c);
};

#endif
