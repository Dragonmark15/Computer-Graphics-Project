#include "Scene.h"

Scene::Scene(int argc, char *argv[])
{
	useNormalForColor = false;//Set to true to test normals

	GraphicsArgs args;
 	args.process(argc, argv);
	
	//Set scene data retrieved from args
	if(args.outputFileName != "") outputFileName = args.outputFileName;
	else outputFileName = "Untitled";
	sceneWidth = args.width;
	sceneHeight = args.height;
	bgColor.set(0.25,0.25,0.25);	//Set a default value, in case XML doesn't specify
/* .obj code
	trianglePointerVector = OBJparse(args);
	Camera newCamera("perspecive", Vector3D(5,0,0), Vector3D(-1,0,0), 1.0, 0.5, sceneWidth, sceneHeight);
	mainCamera = newCamera;
*/
	//Begin data parse
	XMLSceneParser xmlScene;

	// register object creation function with xmlScene
	xmlScene.registerCallback("camera", this);
	xmlScene.registerCallback("light", this);
	xmlScene.registerCallback("shader", this);
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
	float tMax;
	Ray rayIn;
	HitStructure inputHit;
	for (size_t y = 0; y < imData.get_height(); ++y)
	{
		for (size_t x = 0; x < imData.get_width(); ++x)
		{
			
			tMax = 1000000;
			inputHit.normal.set(0,0,0);
			rayIn.origin = mainCamera.getPosition();
			rayIn.direction = mainCamera.genRay(x,y);
			//Iterate through spheres
			for(int i = 0; i < sphereVector.size(); i++)
			{
				sphereVector[i].intersect(rayIn, mainCamera.getFocalLength(), tMax, inputHit);
			}
			//Iterate through triangles
			for(int i = 0; i < triangleVector.size(); i++)
			{
				triangleVector[i].intersect(rayIn, mainCamera.getFocalLength(), tMax, inputHit);
			}
			//Iterate through triangle pointers (OBJ)
			for(int i = 0; i < trianglePointerVector.size(); i++)
			{
				trianglePointerVector[i]->intersect(rayIn, mainCamera.getFocalLength(), tMax, inputHit);
			}
			//Iterate through boxes
			for (int i = 0; i < boxVector.size(); i++)
			{
				boxVector[i].intersect(rayIn, mainCamera.getFocalLength(), tMax, inputHit);
			}
			if(inputHit.normal.length() == 0) { //If miss, set color to background
				imData[y][x] = png::rgb_pixel(bgColor[0]*255, bgColor[1]*255, bgColor[2]*255);
			}
			else {
				Vector3D finalColor;
				std::string type = inputHit.shader.getType();
				if(type == "BlinnPhong")
					finalColor = tempShader->apply(inputHit.normal, inputHit.point, mainCamera.getPosition(), lightVector);
				else if(type == "Lambertian")
					finalColor = inputHit.shader.apply(inputHit.normal, inputHit.point, lightVector);
				if(useNormalForColor) imData[y][x] = png::rgb_pixel((inputHit.normal[0]+1)*127, (inputHit.normal[1]+1)*127, (inputHit.normal[2]+1)*127);
				else imData[y][x] = png::rgb_pixel(finalColor[0]*255, finalColor[1]*255, finalColor[2]*255);
			}
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
		Light newLight(ldata.position, ldata.intensity);
		lightVector.push_back(newLight);
		std::cout << "\tFound Light!" << std::endl;
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
  Shader tempShader;

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

	switch (shape.shader.type) {
		case blinnphong:
		case phong:
		{
			BlinnPhong newShader(shape.shader.kd_diffuse, shape.shader.ks_specular, shape.shader.phongExp);
			tempShader = newShader;
			break;
		}
		case lambertian:
		default:
		{
			Shader newShader(shape.shader.kd_diffuse);
			tempShader = newShader;
			break;
		}
	}

	Sphere newSphere(shape.center, shape.radius, tempShader);
	sphereVector.push_back(newSphere);

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

	switch (shape.shader.type) {
		case blinnphong:
		case phong:
		{
			BlinnPhong newShader(shape.shader.kd_diffuse, shape.shader.ks_specular, shape.shader.phongExp);
			tempShader = newShader;
			break;
		}
		case lambertian:
		default:
		{
			Shader newShader(shape.shader.kd_diffuse);
			tempShader = newShader;
			break;
		}
	}

	Box newBox(shape.minPt, shape.maxPt, tempShader);
	boxVector.push_back(newBox);
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

	switch (shape.shader.type) {
		case blinnphong:
		case phong:
		{
			BlinnPhong newShader(shape.shader.kd_diffuse, shape.shader.ks_specular, shape.shader.phongExp);
			tempShader = newShader;
			break;
		}
		case lambertian:
		default:
		{
			Shader newShader(shape.shader.kd_diffuse);
			tempShader = newShader;
			break;
		}
	}

	Triangle newTriangle(shape.v0, shape.v1, shape.v2, tempShader);
	triangleVector.push_back(newTriangle);

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

std::vector<Triangle*> Scene::OBJparse(GraphicsArgs args){

	// Store all triangles in the OBJ file in a triangle list
	// this is the primary list of all geometry in the 3D model
	// that we will build up while iterating over the structures
	// in the OBJ file data.
	std::vector<Triangle*> triangleList;

	// ///////////////////////////////
	// the following code is needed for reading the OBJ files and
	// parsing out their data.

	// After reading in the entire OBJ file, we will keep a list of 
	// ALL vertices in the 3D object, these will be stored in the 
	// vertexList object. I call it a list for simplicity but
	// it is implemented as a STL vector.
	std::vector<Vector3D> vertexList;
 
	// For efficiency in large 3D models, many vertices can and are
	// re-used, especially where multiple triangles meet at a point. This
	// is managed by what is called an Indexed Triangle list. The incides
	// in this list refer to vertices in the vertexList. Sets of 3 indices
	// represent a single triangle.
	std::vector<int> indexList;
 
	std::string filename; // need to fill this out yourself!
	if (args.inputFileName != "")
		filename = args.inputFileName;
	else
	{
		std::cerr << "Need input file!" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cerr << "Reading OBJ file: " << filename << "..." << std::endl;
 
	// The ModelOBJ class comes from the header model_obj.h. We will
	// use this class to read the OBJ file. After it is read, we will
	// extract the elements needed to create a list of triangles.
	ModelOBJ mOBJ;
	if (mOBJ.import( filename.c_str() ))
 		std::cout << "...loading successful." << std::endl;
	else {
 		std::cout << "...unsuccessful! Exiting!" << std::endl;
 		exit(EXIT_FAILURE);
	}

	std::cout << "Number of meshes contained within OBJ: " << mOBJ.getNumberOfMeshes() << std::endl;
	std::cout << "Number of triangles contained within OBJ: " << mOBJ.getNumberOfTriangles() << std::endl;

	const ModelOBJ::Mesh *pMesh = 0;
	const ModelOBJ::Vertex *pVertices = 0;

	const int *idxBuffer = mOBJ.getIndexBuffer();

	// OBJ files can contain multiple "meshes". Each mesh can contain a
	// variety of triangles. Here we will loop over all the meshes and
	// extract out all the triangles in each mesh.
	for (int mIdx=0; mIdx<mOBJ.getNumberOfMeshes(); mIdx++) {

   		// Obtain pointers to the mesh data and the vertex list
   		pMesh = &mOBJ.getMesh(mIdx);
   		pVertices = mOBJ.getVertexBuffer();

   		// Some meshes come with shading data embedded in them, such as
   		// diffuse and specular components. I am leaving this out for now,
   		// but if you find yourself interested, you could extract the
   		// material properties out of the mesh like this:
   		// 
   		// const ModelOBJ::Material *pMaterial = 0;
   		// pMaterial = pMesh->pMaterial;
   		// std::cout << "Diffuse component: " << pMaterial->diffuse[0]
   		// << ", " << pMaterial->diffuse[1]
   		// << ", " << pMaterial->diffuse[2] << std::endl;

   		// Iterate over all indices in this mesh
   		for (int i=pMesh->startIndex; i<(pMesh->startIndex + pMesh->triangleCount*3); i+=3) {

		    // The model_obj.h class contains it's OWN Vertex class. We
      		// extract the three vertices using the indices here to make it
      		// obvious where the data is coming from
      		ModelOBJ::Vertex v0, v1, v2;
      		v0 = pVertices[ idxBuffer[i] ];
      		v1 = pVertices[ idxBuffer[i+1] ];
      		v2 = pVertices[ idxBuffer[i+2] ];
 
      		// Place these three vertices into our Vector3D class which is
      		// used for the Triangle class.
      		Vector3D tv0(v0.position[0],v0.position[1],v0.position[2]);
      		Vector3D tv1(v1.position[0],v1.position[1],v1.position[2]);
      		Vector3D tv2(v2.position[0],v2.position[1],v2.position[2]);

      		// Note that with the following step, we are losing the
      		// efficiency of the indexed triangle list since we end up making
      		// individual triangles without sharing data. If you are
      		// interested in changing this in your own code, go for it! Let me
      		// know if you do this!
      		// 
      		// Using the actual vertices of the triangle, instance a new triangle!
      		Triangle *tPtr = new Triangle( tv0, tv1, tv2 );

      		// In case you're interested, the OBJ files also provide the
      		// normal vectors at each vertex. You can access them like this:
      		// 
      		// v0.normal[0]
      		// v0.normal[1]
      		// v0.normal[2]
      		// and so on for each vertex
		
      		// be sure to add this triangle onto the triangle list
      		triangleList.push_back(tPtr);
    	} 
	}
	return triangleList;
}
