#ifndef __BLINN_PHONG_H__
#define __BLINN_PHONG_H__

#include <math.h>
#include <string>

#include "Vector3D.h"
#include "Shader.h"
#include "Light.h"

using namespace sivelab;

class BlinnPhong : public Shader {
public:
	BlinnPhong(Scene* inputScenePtr);
	BlinnPhong(Scene* inputScenePtr, Vector3D inputDiffuse, Vector3D inputSpecular, float inputPhong);
	BlinnPhong(Scene* inputScenePtr, Vector3D inputDiffuse, Vector3D inputSpecular, float inputPhong, float inputAmbient);
	void setSpecular(Vector3D inputSpecular) {specular = inputSpecular;}
	Vector3D getSpecular() {return specular;}
	void setPhong(float inputPhong) {phong = inputPhong;}
	float getPhong() {return phong;}
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue);
protected:
	Vector3D specular;
	float phong;
};

#endif
