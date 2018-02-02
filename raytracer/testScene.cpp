#include <iostream>
#include <cstdlib>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Vector3D.h"
#include "camera.h"
#include "shape.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);



  //
  // Create a red image
  //
  int w = args.width, h = args.height;
  png::image< png::rgb_pixel > imData( w, h );
  for (size_t y = 0; y < imData.get_height(); ++y)
    {
      for (size_t x = 0; x < imData.get_width(); ++x)
	{
	  // non-checking equivalent of image.set_pixel(x, y, ...);
	  imData[y][x] = png::rgb_pixel(255, 0, 0);
	}
    }
  imData.write( "red_DualLoop.png" );
}

