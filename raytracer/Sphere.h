#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "Vector3D.h"
#include "Shape.h"

using namespace sivelab;
struct tValue {
	bool t1real;
	bool t2real;
	double t1;
	double t2;
};

class Sphere : public Shape {
public:
	~Sphere(){}
	Sphere(Vector3D inputCenter, float inputRadius);
	Sphere(Vector3D inputCenter, float inputRadius, Vector3D inputColor);

	//void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	//bool intersect(const Vector3D origin, const Vector3D direction);

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit);
	bool intersect(const Ray rayIn);

	Vector3D getColor() {return hit.color;}
private:
	Vector3D center;
	float radius;
	Vector3D calculateNormal();
	tValue calculateT(const Vector3D origin, const Vector3D direction);
	tValue calculateT(const Ray rayIn);
};

#endif
