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

	Camera mainCamera("perspective",
					  Vector3D inputPosition(0,0,0),
					  Vector3D inputDirection(0,0,-1),
					  1.0,
					  0.5,
					  args.width,
					  args.height);
	Sphere sphere0(Vector3D inputCenter(0,0,-5), 1.0);
	//
	// Create a red sphere
	//
	//int w = args.width, h = args.height;
	png::image< png::rgb_pixel > imData( mainCamera.getPixelWidth(), mainCamera.getPixelHeight() );
	for (size_t y = 0; y < imData.get_height(); ++y)
	{
		for (size_t x = 0; x < imData.get_width(); ++x)
		{
			if(sphere0.intersect(mainCamera.getPosition(),mainCamera.genRay(x,y)))
			{
				imData[y][x] = png::rgb_pixel(255, 0, 0);
			}
			else imData[y][x] = png::rgb_pixel(50, 50, 50);
		}
	}
	imData.write( "red_DualLoop.png" );
}

