#include "Shader.h"

Vector3D Shader::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector) {
	Vector3D finalColor;// = diffuse * ambient; //Ambient color
	Vector3D lightDirection;
	lightDirection = lightVector.getPosition() - location;
	lightDirection.normalize();
	finalColor += (diffuse * lightVector.getIntensity() * fmax(0, inputNormal.dot(lightDirection)));
	return finalColor;
}
