#include "Reflective.h"
#include "Scene.h"

Reflective::Reflective(Scene* inputScenePtr) { 
	scenePtr = inputScenePtr;
	diffuse.set(0,0,0);
	type = "Mirror";
	ambient = 0.1;
}
/*
Reflective::Reflective(Scene* inputScenePtr, Vector3D inputDiffuse) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	type = "Glaze";
	ambient = 0.1;
}
Reflective::Reflective(Scene* inputScenePtr, Vector3D inputDiffuse, float inputAmbient) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	type = "Glaze";
	ambient = inputAmbient;
}
*/
Vector3D Reflective::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D viewOrigin, Light lightVector, int recursionValue) {
	Vector3D finalColor(0,0,0);	
	if(recursionValue > 0) {
		Ray rayIn;
		rayIn.origin = location;
		Vector3D viewDir = location - viewOrigin;
		rayIn.direction = viewDir - (2 * (viewDir.dot(inputNormal)) * inputNormal);
		finalColor = scenePtr->raycolor(rayIn, 1e-7, 1e7, --recursionValue);
	}
	return finalColor;
}

