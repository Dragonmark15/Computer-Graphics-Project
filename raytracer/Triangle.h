#ifndef __SPHERE_H__
#define __SPHERE_H__

//#include <string>

#include "Vector3D.h"
#include "Shape.h"

class Triangle : public Shape {
public:
	~Triangle(){}
	Triangle(Vector3D v0, Vector3D v1, Vector3D v2);
	Triangle(Vector3D v0, Vector3D v1, Vector3D v2, Vector3D inputColor);
	void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	bool intersect(const Vector3D origin, const Vector3D direction);
	Vector3D getColor() {return color;}
	/*
	virtual void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, HitStructure &h);
	virtual bool intersect(const Vector3D origin, const Vector3D direction);
	*/
protected:
	Vector3D v0, v1, v2;

//tValue calculateT(const Vector3D origin, const Vector3D direction);
/*	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};*/
};

#endif
