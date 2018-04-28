#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Vector3D.h"
#include "Shape.h"
#include "Shader.h"

class Triangle : public Shape {
public:
	~Triangle(){}
	Triangle(std::string inName, Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Shader* inputShader);

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit);
	bool intersect(const Ray rayIn);

	Vector3D getPoints(int vertex);

private:
	Vector3D v0, v1, v2;
	Vector3D v0color, v1color, v2color; //Used for per-vertex shading in rasterizer
	float calculateT(const Ray rayIn);
	float triangleArea(const Vector3D a, const Vector3D b, const Vector3D c);
};

#endif
