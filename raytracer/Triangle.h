#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Vector3D.h"
#include "Shape.h"

class Triangle : public Shape {
public:
	~Triangle(){}
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2);
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Vector3D inputColor);
	//void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	//bool intersect(const Vector3D origin, const Vector3D direction);
	Vector3D getColor() {return hit.color;}
	Vector3D getNormal() {return hit.normal;}

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit);
	bool intersect(const Ray rayIn);

private:
	Vector3D v0, v1, v2;
	//Vector3D barCoordinates(const Ray rayIn);
	float calculateT(const Ray rayIn);
	float triangleArea(const Vector3D a, const Vector3D b, const Vector3D c);
};

#endif
