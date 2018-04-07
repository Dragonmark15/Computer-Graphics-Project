#ifndef __REFLECTIVE_H__
#define __REFLECTIVE_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Shader.h"
#include "Light.h"

using namespace sivelab;

class Scene; // Forward Declaration

class Reflective : public Shader {
public:
	Reflective(Scene* inputScenePtr); //Uses a scene pointer in order to get the objects for 
	Reflective(Scene* inputScenePtr, Vector3D inputReflectColor);
	Reflective(Scene* inputScenePtr, Vector3D inputReflectColor, float inputAmbient);
	void setReflectColor(Vector3D inputReflectColor) {reflectColor = inputReflectColor;}
	Vector3D getReflectColor() {return reflectColor;}
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector);
protected:
	Vector3D reflectColor;
	Scene* scenePtr;
};

#endif
