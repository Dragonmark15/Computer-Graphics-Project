#ifndef __SCENE_H__
#define __SCENE_H__

#include <string>
#include <vector>
#include <math.h>

// Need to include the header of the code that reads and parses the
// OBJ file
#include "model_obj.h"

#include "Vector3D.h"
#include "Camera.h"
#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "RaytracerClasses.h"
#include "Light.h"
#include "Shader.h"
#include "Blinn-Phong.h"
#include "Reflective.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Box.h"
#include "XMLSceneParser.h"
#include "SceneDataTypes.h"

using namespace sivelab;
using boost::property_tree::ptree;

class Scene : public sivelab::SceneElementCreator {
public:
	Scene(int argc, char *argv[]);
	void genImage();
	bool useNormalForColor;
	void instance( ptree::value_type const &v ); 
	std::vector<Shape*> getShapeVector() {return shapeVector;}
	int getReflectiveEnergy() {
		reflectiveEnergy--;
		return reflectiveEnergy;
	}
private:
	std::string outputFileName;
	Vector3D bgColor;
	Camera mainCamera;
	std::vector<Shape*> shapeVector;
	std::vector<Light> lightVector;
	int sceneWidth;
	int sceneHeight;
	int reflectiveEnergy; //Used for reflections to determine the level of recussion allowed

    void parseShapeData( ptree::value_type const &v );
    shaderData* parseShaderData( ptree::value_type const &v );

	void OBJparse(GraphicsArgs args);
    
    // std::map<std::string, Texture*> textureSources;
    std::map<std::string, shaderData*> shaderMap;
};

#endif
