#include "Blinn-Phong.h"

Vector3D BlinnPhong::apply(const Vector3D inputNormal, const Vector3D location, const Vector3D cameraLocation, std::vector<Light> lightVector) {
	Vector3D finalColor = diffuse * 0.1; //Ambient color
	Vector3D lightDirection, halfVector;
	Vector3D viewDirection = cameraLocation - location;
	viewDirection.normalize();
	for(int i = 0; i < lightVector.size(); i++) {
		lightDirection = lightVector[i].getPosition() - location;
		lightDirection.normalize();
		halfVector = (viewDirection + lightDirection) / (viewDirection + lightDirection).length();
		finalColor += (diffuse * lightVector[i].getIntensity() * fmax(0, inputNormal.dot(lightDirection))) + (specular * lightVector[i].getIntensity() * pow(fmax(0, inputNormal.dot(halfVector)),phong));
	}
	finalColor.clamp(0,1);
	return finalColor;
}
