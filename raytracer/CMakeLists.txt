include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/raytracer)

add_executable(Ray_Tracer
	Scene.cpp
	camera.h camera.cpp
	shape.h
	sphere.cpp sphere.h
)

target_link_libraries(Ray_Tracer sive-util)
target_link_libraries(Ray_Tracer ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(Ray_Tracer ${PNG_LIBRARY})
target_link_libraries(Ray_Tracer ${ZLIB_LIBRARY})
