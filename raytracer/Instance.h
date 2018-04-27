#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include "Vector3D.h"
#include "Matrix4x4.h"
#include "Shape.h"
#include "Shader.h"

using namespace sivelab;

class Instance : public Shape {
public:
	~Instance(){}
	Instance(Matrix4x4 inputM, Shape* inputOriginal, Shader* inputShader);

	void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit);
	bool intersect(const Ray rayIn);

private:
	Matrix4x4 Minv;
	Shape* original;
};

#endif
