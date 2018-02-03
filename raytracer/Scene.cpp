#include <iostream>
#include <cstdlib>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Vector3D.h"
#include "camera.h"
#include "sphere.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
	GraphicsArgs args;
 	args.process(argc, argv);
	Vector3D cameraPosition(0,0,0);
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
	Sphere sphere0(sphereCenter, 1.0, sphereColor);
	//
	// Create a red sphere
	//
	//int w = args.width, h = args.height;
	png::image< png::rgb_pixel > imData( mainCamera.getPixelWidth(), mainCamera.getPixelHeight() );
	Vector3D sceneColor;
	float dummyTMax; //For one sphere, this does nothing, but is still required
	for (size_t y = 0; y < imData.get_height(); ++y)
	{
		for (size_t x = 0; x < imData.get_width(); ++x)
		{
			sceneColor.set(50,50,50);//Gray color if the ray misses
			dummyTMax = 1000;
			sphere0.intersect(mainCamera.getPosition(),mainCamera.genRay(x,y), mainCamera.getFocalLength(), dummyTMax, sceneColor);
			imData[y][x] = png::rgb_pixel(sceneColor[0], sceneColor[1], sceneColor[2]);

			/*if(sphere0.intersect(mainCamera.getPosition(),mainCamera.genRay(x,y)))
			{
				imData[y][x] = png::rgb_pixel(x, y, 100);
			}
			else imData[y][x] = png::rgb_pixel(100, 100, 100);*/
		}
	}
	imData.write( "Initial_Sphere_Test.png" );
}

