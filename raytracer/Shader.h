#ifndef __SHADER_H__
#define __SHADER_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Light.h"

class Scene;

class Shader {
public:
	Shader(){};
	Shader(Scene* inputScenePtr) {
		scenePtr = inputScenePtr;
		diffuse.set(.5,.5,.5);
		type = "Lambertian";
		ambient = 0.1;
	}
	Shader(Scene* inputScenePtr, Vector3D inputDiffuse) {
		scenePtr = inputScenePtr;
		diffuse = inputDiffuse;
		type = "Lambertian";
		ambient = 0.1;
	}
	Shader(Scene* inputScenePtr, Vector3D inputDiffuse, float inputAmbient) {
		scenePtr = inputScenePtr;
		diffuse = inputDiffuse;
		type = "Lambertian";
		ambient = inputAmbient;
	}
	~Shader(){}
	void setDiffuse(Vector3D inputDiffuse) {diffuse = inputDiffuse;}
	Vector3D getDiffuse() {return diffuse;}
	float getAmbient() {return ambient;}
	std::string getType() {return type;}
	virtual Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue);
protected:
	Vector3D diffuse;
	float ambient;
	std::string type;
	Scene* scenePtr;
};
#endif
