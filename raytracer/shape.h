#ifndef __SHAPE_H__
#define __SHAPE_H__

//#include <string>

#include "Vector3D.h"

class Shape {
public:
	virtual void intersect(const Vector3D origin, const Vector3D direction, float tMin, float &tMax, Vector3D &inputColor);
	virtual bool intersect(const Vector3D origin, const Vector3D direction);
protected:
	Vector3D color;
/*	struct HitStructure {
		Vector3D color;
		Vector3D surfaceNormal;
	};*/
}

#endif
