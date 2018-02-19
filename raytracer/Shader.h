#ifndef __SHADER_H__
#define __SHADER_H__

#include <math.h>
#include <vector>

#include "Vector3D.h"
#include "Light.h"

class Shader {
public:
	Shader() {diffuse.set(.5,.5,.5);}
	Shader(Vector3D inputDiffuse) {diffuse = inputDiffuse;}
	~Shader(){}
	void set(Vector3D inputDiffuse) {diffuse = inputDiffuse;}
	Vector3D getDiffuse() {return diffuse;}
	virtual Vector3D apply(const Vector3D inputNormal, const Vector3D location, std::vector<Light> lightVector);
private:
	Vector3D diffuse;
};
#endif
