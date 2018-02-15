#!/bin/bash

mkdir -p build
cd build
cmake ..
make
cd ..
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/oneSphere.xml -w 500 -h 500 -o oneSphere.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/oneTriangle.xml -w 500 -h 500 -o oneTriangle.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/threeTriangles.xml -w 500 -h 500 -o threeTriangle.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/spheres_1K.xml -w 500 -h 500 -o spheres_1k.png
