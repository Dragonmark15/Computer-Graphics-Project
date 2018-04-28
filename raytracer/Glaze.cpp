#include "Shader.h"
#include "Scene.h"

Glaze::Glaze(Scene* inputScenePtr, Vector3D inputDiffuse, float inputMirrorCoef) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	ambient = 0.1;
	mirrorCoef = inputMirrorCoef;
	if(mirrorCoef > 1) mirrorCoef = 1;
	if(mirrorCoef < 0) mirrorCoef = 0;
	type = "Glaze";
	lambertianShader = new Shader(scenePtr, diffuse, ambient);
	reflectiveShader = new Reflective(scenePtr);
}

Glaze::Glaze(Scene* inputScenePtr, Vector3D inputDiffuse, float inputAmbient, float inputMirrorCoef) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	ambient = inputAmbient;
	mirrorCoef = inputMirrorCoef;
	type = "Glaze";
	lambertianShader = new Shader(scenePtr, diffuse, ambient);
	reflectiveShader = new Reflective(scenePtr);
}

Vector3D Glaze::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue) {
	Vector3D lamColor = lambertianShader->apply(inputNormal, location, cameraLocation, lightVector, recursionValue);
	Vector3D refColor = reflectiveShader->apply(inputNormal, location, cameraLocation, lightVector, recursionValue);
	return (refColor * (1.0 - mirrorCoef)) + (lamColor * mirrorCoef);
}
