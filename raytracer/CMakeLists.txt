include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/raytracer)

add_library(raytracer
	Camera.cpp Camera.h
	Shape.h
	Sphere.cpp Sphere.h
	Triangle.cpp Triangle.h
	Box.cpp Box.h
	Scene.cpp Scene.h
	SceneDataTypes.h
	RaytracerClasses.h
	Light.h
	Shader.h LambertianShader.cpp
	Blinn-Phong.cpp Blinn-Phong.h
	Reflective.cpp Reflective.h
	Matrix4x4.cpp Matrix4x4.h
	Glaze.cpp Glaze.h
	Instance.cpp Instance.h
)

add_executable(Ray_Tracer
	rayTracerMain.cpp
)

target_link_libraries(Ray_Tracer raytracer)
target_link_libraries(Ray_Tracer sive-util)
target_link_libraries(Ray_Tracer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(Ray_Tracer ${PNG_LIBRARY})
target_link_libraries(Ray_Tracer ${ZLIB_LIBRARY})
