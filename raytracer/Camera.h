#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <string>

#include "Vector3D.h"

using namespace sivelab;

class Camera {
public:
	enum CamType { perspective, orthographic };

	Camera();
	Camera(std::string inputType,
		   Vector3D inputPosition,
		   Vector3D inputDirection,
		   float inputFocalLength,
		   float inputImagePlaneWidth,
		   int inputPixelWidth,
		   int inputPixelHeight);
	~Camera();

	Vector3D genRay(int x, int y);

	int getPixelWidth() {return mainData.pixelWidth;}
	int getPixelHeight() {return mainData.pixelHeight;}
	Vector3D getPosition() {return mainData.position;}
	float getFocalLength() {return mainData.focalLength;}
protected:
	struct cameraData {		
		CamType type;
		Vector3D position;
		Vector3D direction;
		Vector3D U;
		Vector3D V;
		Vector3D W;
		float focalLength, imagePlaneWidth;
		int pixelWidth, pixelHeight;
	};
	cameraData mainData;
	void calculateOrthonormalBasis(); //Used only in constructor to set U,V,W
};

#endif
