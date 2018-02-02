#include <string>

#include "camera.h"

Camera::Camera() {
	
}

Camera::Camera(std::string inputType,
				   Vector3D inputPosition,
				   Vector3D inputDirection,
				   float inputFocalLength,
				   float inputImagePlaneWidth,
				   int inputPixelWidth,
				   int inputPixelHeight) {
	//Set camera type
	if(inputType == "perspective") mainData.type = perspective;
	else if(inputType == "orthographic") mainData.type = orthographic;
	else printf("ERROR: type incorrectly set");
	//Set remaining data
	mainData.position = inputPosition;
	mainData.direction = inputDirection;
	mainData.focalLength = inputFocalLength;
	mainData.imagePlaneWidth = inputImagePlaneWidth;
	mainData.pixelWidth = inputPixelWidth;
	mainData.pixelheight = inputPixelHeight;
}

Camera::~Camera() {

}

Vector3D Camera::genRay(int x, int y) {

}
