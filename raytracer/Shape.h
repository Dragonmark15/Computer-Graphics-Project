#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <string>

#include "Vector3D.h"
#include "RaytracerClasses.h"

using namespace sivelab;

class Shape {
public:
	virtual void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit) = 0;
	virtual bool intersect(const Ray rayIn) = 0;

	virtual Shader* getShader() {return hit.shader;}
	virtual Vector3D getNormal() {return hit.normal;}
	virtual std::string getName() {return name;}

	virtual Vector3D getPoints(int vertex) {return Vector3D(0,0,0);} //Default statement, made so the rasterizer can get the triangle points
protected:
	HitStructure hit;
	std::string name;
};

#endif
