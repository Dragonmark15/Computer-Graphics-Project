#ifndef __SCENE_H__
#define __SCENE_H__

//#include <string>

//#include "Vector3D.h"
#include "shape.h"
#include "camera.h"

class Scene {
public:
	

protected:
	std::list<Shape> ShapeList;
	Camera mainCamera;
	
}

#endif
