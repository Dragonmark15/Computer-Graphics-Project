#!/bin/bash

mkdir -p build
cd build
cmake ..
make
cd ..
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/spheres_1K.xml -w 500 -h 500 -o spheres_1k.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/PhongExp.xml -w 500 -h 500 -o PhongExp.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/mirrorTest.xml -w 500 -h 500 -o mirrorTest.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/mirroredScene.xml -w 500 -h 500 -o mirroredScene.png
./build/raytracer/Ray_Tracer -i ../sceneData/scenes_A/CornellRoom_wMirroredSpheres.xml -w 500 -h 500 -o CornellRoom.png
