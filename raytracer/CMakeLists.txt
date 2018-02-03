include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(test_scene
	testScene.cpp,
	camera.h camera.cpp
	shape.h
	sphere.cpp sphere.h
)

target_link_libraries(test_scene sive-util)
target_link_libraries(test_scene ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(test_scene ${PNG_LIBRARY})
target_link_libraries(test_scene ${ZLIB_LIBRARY})
