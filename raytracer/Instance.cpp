#include "Instance.h"

Instance::Instance(std::string inName, Shape* inputOriginal, Shader* inputShader) {
	name = inName;
	Minv = hardcodeMinv();
	original = inputOriginal;
	hit.shader = inputShader;
}

void Instance::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	Ray instanceRay;
	float oldTMax = tMax; //Used to determine if the shader should override. If tMax changes, it hit
	double w = 1;
	instanceRay.origin = Minv.multVector(rayIn.origin, w);
	w = 0;
	instanceRay.direction = Minv.multVector(rayIn.direction, w);
	original->intersect(instanceRay, tMin, tMax, inputHit);
	if (oldTMax != tMax) {
		inputHit.shader = hit.shader;
		w = 1;
		inputHit.normal = Minv.transpose().multVector(inputHit.normal, w);
	}
}

bool Instance::intersect(const Ray rayIn) {
	Ray instanceRay;
	double w = 1;
	instanceRay.origin = Minv.multVector(rayIn.origin, w);
	w = 0;
	instanceRay.direction = Minv.multVector(rayIn.direction, w);
	return original->intersect(instanceRay);
}

Matrix4x4 Instance::hardcodeMinv() {
	Matrix4x4 scale(2,0,0,0,
					0,4,0,0,
					0,0,2,0,
					0,0,0,1);
	Matrix4x4 shear(1,	0.5,0.5,0,
					0,	1,	0,	0,
					0,	0,	1,	0,
					0,	0,	0,	1);
	Matrix4x4 move(	1,0,0,-6,
					0,1,0,0,
					0,0,1,-2.5,
					0,0,0,1);
	Matrix4x4 M = move * shear * scale;

	return M.inverse();
}
