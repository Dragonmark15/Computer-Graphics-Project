#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

//#include <string>

#include "Vector3D.h"
#include "Shape.h"

class Triangle : public Shape {
public:
	~Triangle(){}
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2);
	Triangle(Vector3D inputv0, Vector3D inputv1, Vector3D inputv2, Vector3D inputColor);
	void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	bool intersect(const Vector3D origin, const Vector3D direction);
	Vector3D getColor() {return color;}
	Vector3D getNormal() {return normal;}
	/*
	virtual void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, HitStructure &h);
	virtual bool intersect(const Vector3D origin, const Vector3D direction);
	*/
private:
	Vector3D v0, v1, v2, normal;
	Vector3D barCoordinates(const Vector3D vectorIn);
	float calculateT(const Vector3D origin, const Vector3D direction, const Vector3D barCoordinates);

//tValue calculateT(const Vector3D origin, const Vector3D direction);
/*	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};*/
};

#endif
