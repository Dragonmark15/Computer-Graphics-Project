#include "Instance.h"

Instance::Instance(Matrix4x4 inputM, Shape* inputOriginal, Shader* inputShader) {
	Matrix4x4 tempM = inputM;
	Minv = tempM.inverse();
	original = inputOriginal;
	hit.shader = inputShader;
}

void Instance::intersect(const Ray rayIn, float tMin, float &tMax, HitStructure &inputHit) {
	Ray instanceRay;
	float oldTMax = tMax; //Used to determine if the shader should override. If tMax changes, it hit
	double w = 1;
	instanceRay.origin = Minv.multVector(rayIn.origin, w);
	w = 1;
	instanceRay.direction = Minv.multVector(rayIn.direction, w);
	original->intersect(instanceRay, tMin, tMax, inputHit);
	if (oldTMax != tMax)
		inputHit.shader = hit.shader;
}

bool Instance::intersect(const Ray rayIn) {
	Ray instanceRay;
	double w = 1;
	instanceRay.origin = Minv.multVector(rayIn.origin, w);
	w = 1;
	instanceRay.direction = Minv.multVector(rayIn.direction, w);
	return original->intersect(instanceRay);
}