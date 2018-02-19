#ifndef __SHAPE_H__
#define __SHAPE_H__

//#include <string>

#include "Vector3D.h"
#include "RaytracerClasses.h"

using namespace sivelab;

class Shape {
public:
	virtual void intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &hit) = 0;
	virtual bool intersect(const Ray rayIn) = 0;
protected:
	HitStructure hit;
};

#endif
