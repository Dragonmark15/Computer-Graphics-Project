#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <string>

#include "Vector3D.h"

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
protected:
	struct cameraData {		
		CamType type;
		Vector3D position;
		Vector3D direction;
		float focalLength;
		float imagePlaneWidth;
		int pixelWidth, pixelHeight;
	}
	cameraData mainData;

}

#endif
