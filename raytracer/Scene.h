#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <stack>

#include "Vector3D.h"
#include "Camera.h"
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Sphere.h"
#include "XMLSceneParser.h"
#include "SceneFile_Instancer.h"

using namespace sivelab;

class Scene : public sivelab::SceneElementCreator {
public:
	Scene(int argc, char *argv[]);
	void genImage();

	void instance( ptree::value_type const &v ); 
private:
	std::string outputFileName;
	Vector3D bgColor;
	Camera mainCamera;
	std::stack<Shape> shapeStack;

    void parseShapeData( ptree::value_type const &v );
    shaderData* parseShaderData( ptree::value_type const &v );
    
    // std::map<std::string, Texture*> textureSources;
    std::map<std::string, shaderData*> shaderMap;
};
