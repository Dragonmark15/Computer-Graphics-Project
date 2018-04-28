#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <string>

#include "Vector3D.h"
#include "Shape.h"
#include "Shader.h"

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
	Sphere(std::string inName, Vector3D inputCenter, float inputRadius, Shader* inputShader);

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit);
	bool intersect(const Ray rayIn);

	Shader* getShader() {return hit.shader;}
private:
	Vector3D center;
	float radius;
	tValue calculateT(const Vector3D origin, const Vector3D direction);
	tValue calculateT(const Ray rayIn);
};

#endif
