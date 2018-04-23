#ifndef __REFLECTIVE_H__
#define __REFLECTIVE_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Shader.h"
#include "Light.h"

using namespace sivelab;

class Reflective : public Shader {
public:
	Reflective(Scene* inputScenePtr);
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue);
};

#endif
