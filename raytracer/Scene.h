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
#include "Glaze.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Box.h"
#include "Instance.h"
#include "XMLSceneParser.h"
#include "SceneDataTypes.h"
#include "Matrix4x4.h"

using namespace sivelab;
using boost::property_tree::ptree;

class Scene : public sivelab::SceneElementCreator {
public:
	Scene(int argc, char *argv[]);
	void genImage();
	void instance( ptree::value_type const &v ); 
	Vector3D raycolor(Ray rayIn, float tMin, float tMax, int recursionValue);
	bool hasDirectLight(Vector3D location, Light light);
private:
	std::string inputFileName;
	std::string outputFileName;
	Vector3D bgColor;
	Camera mainCamera;
	std::vector<Shape*> shapeVector;
	std::vector<Light> lightVector;
	int sceneWidth;
	int sceneHeight;
	int recursion;
	bool rasterization;
	int rpp;

	void rasterize();
	float rasterBaryCoords(Vector3D vec0, Vector3D vec1, float x, float y);
    void parseShapeData( ptree::value_type const &v );
    shaderData* parseShaderData( ptree::value_type const &v );

	void OBJparse(GraphicsArgs args);
    
    // std::map<std::string, Texture*> textureSources;
    std::map<std::string, shaderData*> shaderMap;
};

#endif
