#include "Blinn-Phong.h"

Vector3D BlinnPhong::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, Light lightVector) {
	Vector3D finalColor;// = diffuse * ambient; //Ambient color
	Vector3D lightDirection, halfVector;
	Vector3D viewDirection = cameraLocation - location;
	viewDirection.normalize();
	lightDirection = lightVector.getPosition() - location;
	lightDirection.normalize();
	halfVector = (viewDirection + lightDirection) / (viewDirection + lightDirection).length();
	finalColor += (diffuse * lightVector.getIntensity() * fmax(0, inputNormal.dot(lightDirection))) + (specular * lightVector.getIntensity() * pow(fmax(0, inputNormal.dot(halfVector)),phong));
	return finalColor;
}
