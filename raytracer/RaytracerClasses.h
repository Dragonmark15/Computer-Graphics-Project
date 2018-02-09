#ifndef __RAYTRACERCLASSES_H__
#define __RAYTRACERCLASSES_H__

#include "Vector3D.h"

using namespace sivelab;

struct Ray {
	Vector3D origin;
	Vector3D direction;
};

struct HitStructure {
	Vector3D color;
	//shader
	Vector3D normal;
};

#endif
