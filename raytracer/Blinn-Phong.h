#ifndef __BLINN_PHONG_H__
#define __BLINN_PHONG_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Shader.h"
#include "Light.h"

using namespace sivelab;

class BlinnPhong : public Shader {
public:
	BlinnPhong() {
		diffuse.set(.5,.5,.5);
		specular.set(1,1,1);
		phong = 8;
		type = "BlinnPhong";
	}
	BlinnPhong(Vector3D inputDiffuse, Vector3D inputSpecular, float inputPhong) {
		diffuse = inputDiffuse;
		specular = inputSpecular;
		phong = inputPhong;
		type = "BlinnPhong";
	}
	void setSpecular(Vector3D inputSpecular) {specular = inputSpecular;}
	Vector3D getSpecular() {return specular;}
	void setPhong(float inputPhong) {phong = inputPhong;}
	float getPhong() {return phong;}
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, std::vector<Light> lightVector);
protected:
	Vector3D specular;
	float phong;
};

#endif
