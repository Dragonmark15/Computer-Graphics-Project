#ifndef __SHADER_H__
#define __SHADER_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Light.h"

class Shader {
public:
	Shader() {
		diffuse.set(.5,.5,.5);
		type = "Lambertian";
	}
	Shader(Vector3D inputDiffuse) {
		diffuse = inputDiffuse;
		type = "Lambertian";
	}
	~Shader(){}
	void setDiffuse(Vector3D inputDiffuse) {diffuse = inputDiffuse;}
	Vector3D getDiffuse() {return diffuse;}
	std::string getType() {return type;}
	virtual Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, std::vector<Light> lightVector);
protected:
	Vector3D diffuse;
	std::string type;
};
#endif
