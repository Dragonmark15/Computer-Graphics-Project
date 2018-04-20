#include "Shader.h"
#include "Scene.h"

Vector3D Shader::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector, int recursionValue) {
	Vector3D finalColor = diffuse * ambient;
	if(scenePtr->hasDirectLight(location, lightVector)) {
		Vector3D lightDirection;
		lightDirection = lightVector.getPosition() - location;
		lightDirection.normalize();
		finalColor += (diffuse * lightVector.getIntensity() * fmax(0, inputNormal.dot(lightDirection)));
	}
	else {
		finalColor = diffuse * ambient;
	}
	return finalColor;
}
