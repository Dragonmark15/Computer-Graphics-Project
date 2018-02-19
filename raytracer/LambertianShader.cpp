#include "Shader.h"

Vector3D Shader::apply(const Vector3D inputNormal, const Vector3D location, std::vector<Light> lightVector) {
	Vector3D finalColor;
	Vector3D lightDirection;
	for(int i = 0; i < lightVector.size(); i++) {
		lightDirection = lightVector[i].getPosition() - location;
		lightDirection.normalize();
		std::cout << "Diffuse: " << diffuse << std::endl;
		std::cout << "Light Intensity: " << lightVector[i].getIntensity() << std::endl;
		std::cout << "Dot product: " << inputNormal.dot(lightDirection) << std::endl;
		std::cout << "FMax: " << fmax(0, inputNormal.dot(lightDirection)) << std::endl;
		finalColor += (diffuse * lightVector[i].getIntensity() * fmax(0, inputNormal.dot(lightDirection)));
	}
	return finalColor;
}
