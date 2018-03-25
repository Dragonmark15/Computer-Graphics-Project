#include "Shader.h"

Vector3D Shader::apply(const Vector3D inputNormal, const Vector3D location, std::vector<Light> lightVector) {
	Vector3D finalColor = diffuse * 0.1; //Ambient color
	Vector3D lightDirection;
	for(int i = 0; i < lightVector.size(); i++) {
		lightDirection = lightVector[i].getPosition() - location;
		lightDirection.normalize();
		finalColor += (diffuse * lightVector[i].getIntensity() * fmax(0, inputNormal.dot(lightDirection)));
	}
	finalColor.clamp(0,1);
	return finalColor;
}
