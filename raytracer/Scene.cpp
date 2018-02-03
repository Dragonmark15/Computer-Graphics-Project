#include <iostream>
#include <cstdlib>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Vector3D.h"
#include "camera.h"
#include "sphere.h"
#include "XMLSceneParser.h"
#include "SceneFile_Instancer.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
	GraphicsArgs args;
 	args.process(argc, argv);
//Hard-Coded data
/*	Vector3D cameraPosition(0,0,0);
	Vector3D cameraDirection(0,0,-1);
	Vector3D sphereCenter(0,0,-5);
	Vector3D sphereColor(0,0,255); //Completely blue based on PNG colors
	Camera mainCamera("perspective",
					  cameraPosition,
					  cameraDirection,
					  1.0,
					  0.5,
					  args.width,
					  args.height);
	Sphere sphere0(sphereCenter, 1.0, sphereColor);*/

	//Begin data parse
	XMLSceneParser xmlScene;

	SceneFile_Instancer *sceneFactory = new SceneFile_Instancer();

	// register object creation function with xmlScene
	xmlScene.registerCallback("camera", sceneFactory);
	//xmlScene.registerCallback("light", sceneFactory); //TODO:Pulled for now, since lights haven't been implimented
	xmlScene.registerCallback("shader", sceneFactory);
	xmlScene.registerCallback("shape", sceneFactory);

	if (args.inputFileName != "")
		xmlScene.parseFile( args.inputFileName );
	else
	{
		std::cerr << "Need input file!" << std::endl;
		exit(EXIT_FAILURE);
	}

	sceneFactory->instance(           );





	png::image< png::rgb_pixel > imData( mainCamera.getPixelWidth(), mainCamera.getPixelHeight() );
	Vector3D pixelColor;
	float dummyTMax;
	for (size_t y = 0; y < imData.get_height(); ++y)
	{
		for (size_t x = 0; x < imData.get_width(); ++x)
		{
			pixelColor.set(args.bgColor);
			dummyTMax = 1000;
			sphere0.intersect(mainCamera.getPosition(),mainCamera.genRay(x,y), mainCamera.getFocalLength(), dummyTMax, pixelColor);
			imData[y][x] = png::rgb_pixel(pixelColor[0], pixelColor[1], pixelColor[2]);

			/*if(sphere0.intersect(mainCamera.getPosition(),mainCamera.genRay(x,y)))
			{
				imData[y][x] = png::rgb_pixel(x, y, 100);
			}
			else imData[y][x] = png::rgb_pixel(100, 100, 100);*/
		}
	}
	if(args.outputFileName != "") imData.write( args.outputFileName );
	else imData.write( "Untitled" );
}
