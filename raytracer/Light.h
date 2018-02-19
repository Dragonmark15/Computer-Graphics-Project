#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "Vector3D.h"

using namespace sivelab;

class Light {
public:
	Light(Vector3D inputPosition, Vector3D inputIntensity) {
		position = inputPosition;
		intensity = inputIntensity;
	}
	~Light(){}
	Vector3D getPosition() {return position;}
	Vector3D getIntensity() {return intensity;}
private:
	Vector3D position;
	Vector3D intensity;
};
#endif
