#pragma once
#include Vector3D.h

//enum CamType(perspective, orthographic);

class Camera{
public:
	Camera();
	Camera(Vector3D);
	Camera(Vector3D, Vector3D);
	setPosition(Vector3D);
	setDirection(Vector3D);
	setFOV(float);
	setScreenWidth(float);
	setScreenHeight(float);
private:
	//CamType type;
	Vector3D position;
	Vector3D direction;
	float FOV;
	float screenWidth;
	float screenHeight;
 };