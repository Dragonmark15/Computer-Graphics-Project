#ifndef __RAYTRACERCLASSES_H__
#define __RAYTRACERCLASSES_H__

#include "Vector3D.h"
#include "Shader.h"

using namespace sivelab;

struct Ray {
	Vector3D origin;
	Vector3D direction;
};

struct HitStructure {
	Shader shader;
	Vector3D normal;
	Vector3D point;
};

#endif
