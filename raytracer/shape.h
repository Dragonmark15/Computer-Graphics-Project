#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <string>

#include "Vector3D.h"

class Shape {
public:
	virtual Shape();
	
	virtual void intersect(const Vector3D VectorIn, float tMin, float &tMax, HitStructure &h);
protected:
	std::string ShapeName;

	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};
}

#endif
