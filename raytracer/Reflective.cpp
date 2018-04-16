#include "Reflective.h"

Reflective::Reflective(std::vector<Shape*>* inputShapesPtr) { 
	shapesPtr = inputShapesPtr;
	diffuse.set(0,0,0);
	type = "Mirror";
	ambient = 0.1;
}
Reflective::Reflective(std::vector<Shape*>* inputShapesPtr, Vector3D inputDiffuse) {
	shapesPtr = inputShapesPtr;
	diffuse = inputDiffuse;
	type = "Glaze";
	ambient = 0.1;
}
Reflective::Reflective(std::vector<Shape*>* inputShapesPtr, Vector3D inputDiffuse, float inputAmbient) {
	shapesPtr = inputShapesPtr;
	diffuse = inputDiffuse;
	type = "Glaze";
	ambient = inputAmbient;
}

Vector3D Reflective::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector) {
	float tMax = 1e7;
	HitStructure inputHit;
	inputHit.normal.set(0,0,0);
	Ray rayIn;
	rayIn.origin = location;
	Vector3D viewDir = location - cameraLocation;
	rayIn.direction = viewDir - (2 * (viewDir.dot(inputNormal)) * inputNormal);
	std::vector<Shape*> shapeVector = *shapesPtr;
	//Iterate through all shapes
	for(int i = 0; i < shapeVector.size(); i++)
	{
		shapeVector[i]->intersect(rayIn, 0.00001, tMax, inputHit);
	}
	
	return inputHit.shader->apply(inputHit.normal, inputHit.point, location, lightVector);
}
