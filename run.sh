#!/bin/bash

mkdir -p build
cd build
cmake ..
make
./raytracer/Ray_Tracer -i ../sceneData/scenes_A/oneSphere.xml -w 500 -h 500 -o oneSphere.png
./raytracer/Ray_Tracer -i ../sceneData/scenes_A/oneTriangle.xml -w 500 -h 500 -o oneTriangle.png
./raytracer/Ray_Tracer -i ../sceneData/scenes_A/threeTriangle.xml -w 500 -h 500 -o threeTriangle.png
./raytracer/Ray_Tracer -i ../sceneData/scenes_A/spheres_1k.xml -w 500 -h 500 -o spheres_1k.png
