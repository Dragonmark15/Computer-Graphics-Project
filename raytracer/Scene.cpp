#include "Scene.h"

Scene::Scene(int argc, char *argv[])
{
	GraphicsArgs args;
 	args.process(argc, argv);
	
	//Set scene data retrieved from args
	if(args.outputFileName != "") outputFileName = args.outputFileName;
	else outputFileName = "Untitled";
	sceneWidth = args.width;
	sceneHeight = args.height;
	bgColor.set(50,50,50);	//Set a default value, in case XML doesn't specify

	//Begin data parse
	XMLSceneParser xmlScene;

	//SceneFile_Instancer *sceneFactory = new SceneFile_Instancer();

	// register object creation function with xmlScene
	xmlScene.registerCallback("camera", this);
	xmlScene.registerCallback("light", this); //TODO:Pulled for now, since lights haven't been implimented
	xmlScene.registerCallback("shader", this); //TODO:Pulled for now, since shaders haven't been implimented
	xmlScene.registerCallback("shape", this);

	if (args.inputFileName != "")
		xmlScene.parseFile( args.inputFileName );
	else
	{
		std::cerr << "Need input file!" << std::endl;
		exit(EXIT_FAILURE);
	}

}

void Scene::genImage(){
	png::image< png::rgb_pixel > imData( mainCamera.getPixelWidth(), mainCamera.getPixelHeight() );
	Vector3D pixelColor;
	float tMax;
	for (size_t y = 0; y < imData.get_height(); ++y)
	{
		for (size_t x = 0; x < imData.get_width(); ++x)
		{
			tMax = 1000000;
			pixelColor.set(bgColor);
			//Iterate through spheres
			for(int i = 0; i < sphereDeque.size(); i++)
			{
				sphereDeque[i].intersect(mainCamera.getPosition(),mainCamera.genRay(x,y), mainCamera.getFocalLength(), tMax, pixelColor);
			}
			//Iterate through triangles
			for(int i = 0; i < triangleDeque.size(); i++)
			{
				triangleDeque[i].intersect(mainCamera.getPosition(),mainCamera.genRay(x,y), mainCamera.getFocalLength(), tMax, pixelColor);
			}
			imData[y][x] = png::rgb_pixel(pixelColor[0], pixelColor[1], pixelColor[2]);
		}
	}
	imData.write(outputFileName);

}




void Scene::instance( ptree::value_type const &v )
{
  std::istringstream buf;

  //
  // Scene Parameters
  //
  if (v.first == "sceneParameters") {

      sceneParamData spData;
      
    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<std::string> pBGColor = v.second.get_optional<std::string>("bgColor");
    boost::optional<std::string > pEnvMapPrefix = v.second.get_optional<std::string>("envMapPrefix");

    if (pBGColor) {
      buf.str( *pBGColor );
      buf >> spData.backgroundColor;
      buf.clear();
	  bgColor = spData.backgroundColor;
    }
    if (pEnvMapPrefix) {
      buf.str( *pEnvMapPrefix );
      buf >> spData.envMapPrefix;
      buf.clear();
      
      spData.usesEnvMap = true;
    }
    else {
      spData.usesEnvMap = false;
    }

	

  }

  //
  // CAMERA
  //
  if (v.first == "camera") {

    std::string name, type;
    Vector3D position, viewDir, lookatPoint;
    bool lookatSet = false;
    float focalLength;
    float imagePlaneWidth;

    name = v.second.get<std::string>("<xmlattr>.name");
    type = v.second.get<std::string>("<xmlattr>.type");

    buf.str( v.second.get<std::string>("position") );
    buf >> position;
    buf.clear();

    // LookAtPoint and ViewDir are optional, but one should be specified.
    boost::optional<std::string> plookatPoint = v.second.get_optional<std::string>("lookatPoint");
    boost::optional<std::string > pviewDir = v.second.get_optional<std::string>("viewDir");

    if (plookatPoint) {
      lookatSet = true;
      buf.str( *plookatPoint );
      buf >> lookatPoint; 
      buf.clear();
    } else if (pviewDir) {
      buf.str( *pviewDir );
      buf >> viewDir; 
      buf.clear();
    }

    buf.str( v.second.get<std::string>("focalLength") );
    buf >> focalLength;
    buf.clear();

    buf.str( v.second.get<std::string>("imagePlaneWidth") );
    buf >> imagePlaneWidth;
    buf.clear();

    if (lookatSet) {
      viewDir = lookatPoint - position;
      viewDir.normalize();
    }

    struct cameraData cam;
    cam.position = position;
    cam.gazeDirection = viewDir;
    cam.focalLength = focalLength;
    cam.imagePlaneWidth = imagePlaneWidth;
        
    if (type == "perspective")
        cam.type = perspective;
    else if (type == "orthographic")
        cam.type = orthographic;
	Camera newCamera(type, cam.position, cam.gazeDirection, cam.focalLength, cam.imagePlaneWidth, sceneWidth, sceneHeight);
	mainCamera = newCamera;
    std::cout << "Found Camera!" << std::endl;
  }


  //
  // Light
  //
  if (v.first == "light") {

    std::string type;
    sivelab::Vector3D position, intensity;

    type = v.second.get<std::string>("<xmlattr>.type");

    buf.str( v.second.get<std::string>("position") );
    buf >> position;
    buf.clear();

    buf.str( v.second.get<std::string>("intensity") );
    buf >> intensity;
    buf.clear();

    lightData ldata;
    ldata.position = position;
    ldata.intensity = intensity;

    if (type == "point") {
        ldata.type = point;
    }
    else if (type == "area") {

      sivelab::Vector3D normal;
      buf.str( v.second.get<std::string>("normal") );
      buf >> normal;
      buf.clear();

      float width = 1.0, length = 1.0;
      width = v.second.get<float>("width");
      length = v.second.get<float>("length");

      ldata.normal = normal;
      ldata.width = width;
      ldata.length = length;
    }
  }

  // 
  // Shader
  // 
  if (v.first == "shader") {
    parseShaderData(v);
  }

  // 
  // Shape or Instance
  // 
  if (v.first == "shape" || v.first == "instance") {
    parseShapeData(v);
  }

  // Texture
  if (v.first == "texture") {
      std::cout << "Found texture, but not parsing yet..." << std::endl;
  }
}

void Scene::parseShapeData( ptree::value_type const &v )
{
  bool notInstance = true;
  if (v.first == "instance")
    notInstance = false;

  // Shapes and instances are basically the same thing, but need to be
  // added to different structures within the scene

  std::string type, name;
  type = v.second.get<std::string>("<xmlattr>.type");
  name = v.second.get<std::string>("<xmlattr>.name");

  // Make sure to find the shader data objects; HAVE to include a
  // shader in this version; Need to find the shader in the second part
  // of the shape pair
  shaderData *shaderPtr = 0;
  ptree::const_assoc_iterator it = v.second.find("shader");
  if( it != v.second.not_found() )
    {
      shaderPtr = parseShaderData( *it );
    }

  shapeData shape;

  std::istringstream buf;
  if (type == "sphere") {
    float radius;
    sivelab::Vector3D center;

    buf.str( v.second.get<std::string>("center") );
    buf >> center;
    buf.clear();

    radius = v.second.get<float>("radius");

    shape.type = sphere;
    shape.name = name;
    shape.radius = radius;
    shape.center = center;
    shape.shader = *shaderPtr;
	Sphere newSphere(shape.center, shape.radius, (shape.shader.kd_diffuse * 255));
	sphereDeque.push_back(newSphere);

    std::cout << "\tFound sphere!" << std::endl;
  }

  if (type == "box") {

    sivelab::Vector3D minPt, maxPt;

    buf.str( v.second.get<std::string>("minPt") );
    buf >> minPt;
    buf.clear();

    buf.str( v.second.get<std::string>("maxPt") );
    buf >> maxPt;
    buf.clear();

    shape.type = box;
    shape.name = name;
    shape.minPt = minPt;
    shape.maxPt = maxPt;
    shape.shader = *shaderPtr;
	///////////////////////////
	// Instance the box here
	///////////////////////////
    std::cout << "\tFound box!" << std::endl;
  }

  if (type == "triangle") {
    sivelab::Vector3D v0, v1, v2;

    buf.str( v.second.get<std::string>("v0") );
    buf >> v0;
    buf.clear();

    buf.str( v.second.get<std::string>("v1") );
    buf >> v1;
    buf.clear();

    buf.str( v.second.get<std::string>("v2") );
    buf >> v2;
    buf.clear();

    shape.type = triangle;
    shape.name = name;
    shape.v0 = v0;
    shape.v1 = v1;
    shape.v2 = v2;
    shape.shader = *shaderPtr;
	Triangle newTriangle(shape.v0, shape.v1, shape.v2, (shape.shader.kd_diffuse * 255));
	triangleDeque.push_back(newTriangle);

    std::cout << "\tFound triangle!" << std::endl;
  }
}

shaderData* Scene::parseShaderData( ptree::value_type const &v )
{
  std::string type, name;
  shaderData* shaderPtr_toReturn = 0;

  std::istringstream buf;
  boost::optional<std::string> optShaderRef = v.second.get_optional<std::string>("<xmlattr>.ref");

  if (!optShaderRef) {
    type = v.second.get<std::string>("<xmlattr>.type");
    name = v.second.get<std::string>("<xmlattr>.name");
  }

  // if name exists in the shader map and this is a ref, return the shader pointer
  // otherwise, add the shader if it is NOT a ref and the name doesn't exist
  // final is to throw error

  std::map<std::string, shaderData*>::const_iterator mIterator = shaderMap.find(name);
  if (mIterator == shaderMap.end() && !optShaderRef) {

    // Did not find the shader and it was not a reference, so create and return
    if (type == "Lambertian") {
      sivelab::Vector3D kd;
      buf.str( v.second.get<std::string>("diffuse") );
      buf >> kd;
      buf.clear();

      shaderPtr_toReturn = new shaderData();
      shaderPtr_toReturn->type = lambertian;
      shaderPtr_toReturn->kd_diffuse = kd;

    }
    else if (type == "BlinnPhong" || type == "Phong") {
      sivelab::Vector3D d, s;
      float phongExp;

      buf.str( v.second.get<std::string>("diffuse") );
      buf >> d;
      buf.clear();

      buf.str( v.second.get<std::string>("specular") );
      buf >> s;
      buf.clear();

      phongExp = v.second.get<float>("phongExp");

      shaderPtr_toReturn = new shaderData();

      shaderPtr_toReturn->kd_diffuse = d;
      shaderPtr_toReturn->ks_specular = s;
      shaderPtr_toReturn->phongExp = phongExp;

      if (type == "BlinnPhong") {
          shaderPtr_toReturn->type = blinnphong;
      }
      else {
          shaderPtr_toReturn->type = phong;
      }
    }

    else if (type == "Mirror") {
        shaderPtr_toReturn = new shaderData();
        shaderPtr_toReturn->type = mirror;
    }
     
    shaderPtr_toReturn->name = name;
    shaderMap[name] = shaderPtr_toReturn;
    
    return shaderPtr_toReturn;
  }
  
  else if (optShaderRef) {
    
    // optShaderRef is true, so this should be a shader reference.
    // Attempt to find the shader in the map and return it.
    std::map<std::string, shaderData*>::const_iterator mIterator = shaderMap.find( *optShaderRef );
    if (mIterator != shaderMap.end())
      return mIterator->second;
    else 
      return 0;
  }
  else 
    std::cerr << "Error that should be caught!" << std::endl;
  
  return 0;
}


