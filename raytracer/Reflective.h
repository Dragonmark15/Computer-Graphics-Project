#ifndef __REFLECTIVE_H__
#define __REFLECTIVE_H__

#include <math.h>
#include <vector>
#include <string>

#include "Vector3D.h"
#include "Shader.h"
#include "Light.h"
#include "Shape.h"

using namespace sivelab;

class Reflective : public Shader {
public:
	Reflective(std::vector<Shape*>* inputShapesPtr); //Uses a scene pointer in order to get the objects for 
	Reflective(std::vector<Shape*>* inputShapesPtr, Vector3D inputReflectColor);
	Reflective(std::vector<Shape*>* inputShapesPtr, Vector3D inputReflectColor, float inputAmbient);
	Vector3D apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector);
protected:
	std::vector<Shape*>* shapesPtr;
};

#endif
