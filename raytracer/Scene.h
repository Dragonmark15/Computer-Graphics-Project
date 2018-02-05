#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <list>

#include "Vector3D.h"
#include "Camera.h"
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Sphere.h"
#include "XMLSceneParser.h"
#include "SceneDataTypes.h"

using namespace sivelab;
using boost::property_tree::ptree;

class Scene : public sivelab::SceneElementCreator {
public:
	Scene(int argc, char *argv[]);
	void genImage();

	void instance( ptree::value_type const &v ); 
private:
	std::string outputFileName;
	Vector3D bgColor;
	Camera mainCamera;
	std::list<Shape*> shapeList;
	int sceneWidth;
	int sceneHeight;

    void parseShapeData( ptree::value_type const &v );
    shaderData* parseShaderData( ptree::value_type const &v );
    
    // std::map<std::string, Texture*> textureSources;
    std::map<std::string, shaderData*> shaderMap;
};

#endif
