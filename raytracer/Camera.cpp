#include <string>

#include "Camera.h"

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
	//Set remaining data
	mainData.position = inputPosition;
	mainData.direction = inputDirection;
	mainData.focalLength = inputFocalLength;
	mainData.imagePlaneWidth = inputImagePlaneWidth;
	mainData.pixelWidth = inputPixelWidth;
	mainData.pixelHeight = inputPixelHeight;
}

Camera::~Camera() {

}

//Currently only works for perspective
Vector3D Camera::genRay(int x, int y) { //x,y ranges from [0,pixelWidth] or [0,pixelHeight]
	//convert integers to a number between 0 and pixelWidth or pixelheight
	Vector3D returnVector;
	if((x >= 0 && x <= mainData.pixelWidth) && (y >= 0 && y <= mainData.pixelHeight)) {
		double newX, newY;
		//convert x
		newX = (double)x / (double)mainData.pixelWidth; //Range from [0,1]
		newX -= 0.5; //Range from [-0.5, +0.5]
		newX *= mainData.imagePlaneWidth; //Range from [-iPW/2, +iPW/2]
		//convert y
		newY = (double)y / (double)mainData.pixelHeight;
		newY -= 0.5;
		newY *= mainData.imagePlaneWidth; //TODO:convert this to imagePlaneHeight, if that gets added
		returnVector.set(newX,newY,0); 
		returnVector += mainData.direction; //Add the changes to view direction so that it can follow the camera
	}
	else {
		returnVector.set(0,0,0); //TODO:Fix this. Causes a Div0 error
	}
	return returnVector;
}








