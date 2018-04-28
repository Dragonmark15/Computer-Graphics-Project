#ifndef __GLAZE_H__
#define __GLAZE_H__

#include <iostream>

#include "Vector3D.h"
#include "Light.h"
#include "Shader.h"
#include "Reflective.h"

class Glaze : public Shader {
public:
	Glaze(Scene* inputScenePtr, Vector3D inputDiffuse, float inputMirrorCoef);
	Glaze(Scene* inputScenePtr, Vector3D inputDiffuse, float inputAmbient, float inputMirrorCoef);
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue);
protected:
	double mirrorCoef;
	Shader* lambertianShader;
	Reflective* reflectiveShader;
};
#endif
