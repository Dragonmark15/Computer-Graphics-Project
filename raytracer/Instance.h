#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include <math.h>

#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Shape.h"
#include "Shader.h"

using namespace sivelab;

class Instance : public Shape {
public:
	~Instance(){}
	Instance(std::string inName, Shape* inputOriginal, Shader* inputShader);

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit);
	bool intersect(const Ray rayIn);

private:
	Matrix4x4 Minv;
	Shape* original;
	Matrix4x4 hardcodeMinv();
};

#endif
