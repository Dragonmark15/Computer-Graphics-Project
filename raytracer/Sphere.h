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
	void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	bool intersect(const Vector3D origin, const Vector3D direction);
	Vector3D getColor() {return color;}
private:
	Vector3D center;
	float radius;

	tValue calculateT(const Vector3D origin, const Vector3D direction);
/*	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};*/
};

#endif
