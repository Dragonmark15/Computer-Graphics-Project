#include "Blinn-Phong.h"
#include "Scene.h"

BlinnPhong::BlinnPhong(Scene* inputScenePtr) {
	scenePtr = inputScenePtr;
	diffuse.set(.5,.5,.5);
	specular.set(1,1,1);
	phong = 8;
	type = "BlinnPhong";
	ambient = 0.1;
}
BlinnPhong::BlinnPhong(Scene* inputScenePtr, Vector3D inputDiffuse, Vector3D inputSpecular, float inputPhong) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	specular = inputSpecular;
	phong = inputPhong;
	type = "BlinnPhong";
	ambient = 0.1;
}
BlinnPhong::BlinnPhong(Scene* inputScenePtr, Vector3D inputDiffuse, Vector3D inputSpecular, float inputPhong, float inputAmbient) {
	scenePtr = inputScenePtr;
	diffuse = inputDiffuse;
	specular = inputSpecular;
	phong = inputPhong;
	type = "BlinnPhong";
	ambient = inputAmbient;
}

Vector3D BlinnPhong::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue) {
	Vector3D finalColor = diffuse * ambient;
	if(scenePtr->hasDirectLight(location, lightVector)) {
		Vector3D lightDirection, halfVector;
		Vector3D viewDirection = cameraLocation - location;
		viewDirection.normalize();
		lightDirection = lightVector.getPosition() - location;
		lightDirection.normalize();
		halfVector = (viewDirection + lightDirection) / (viewDirection + lightDirection).length();
		finalColor += (diffuse * lightVector.getIntensity() * fmax(0, inputNormal.dot(lightDirection))) + (specular * lightVector.getIntensity() * pow(fmax(0, inputNormal.dot(halfVector)),phong));
	}
	else {
		finalColor = diffuse * ambient;
	}
	return finalColor;
}
