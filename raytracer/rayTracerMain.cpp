#include <iostream>
#include <cstdlib>

#include "png++/png.hpp"
#include "handleGraphicsArgs.h"
#include "Vector3D.h"

using namespace sivelab;

int main(int argc, char *argv[])
{
  GraphicsArgs args;
  args.process(argc, argv);
}

