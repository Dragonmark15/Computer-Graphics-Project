#ifndef __SPHERE_H__
#define __SPHERE_H__

//#include <string>

#include "Vector3D.h"

class Sphere : public Shape {
public:
	Sphere(Vector3D inputCenter, float inputRadius);
	Sphere(Vector3D inputCenter, float inputRadius, Vector3D inputColor);
	/*
	virtual void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, HitStructure &h);
	virtual bool intersect(const Vector3D origin, const Vector3D direction);
	*/
protected:
	Vector3D center;
	float radius;
	struct tValue {
		bool t1real = false;
		bool t2real = false;
		double t1 = 0;
		double t2 = 0;
	}

tValue calculateT(const Vector3D origin, const Vector3D direction);
/*	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};*/
}

#endif
