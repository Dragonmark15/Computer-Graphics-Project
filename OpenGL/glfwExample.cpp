#include <cstdlib>
#include <iostream>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include "Vector3D.h"
#include "Camera.h"
#include "png++/png.hpp"

#define GLM_FORCE_RADIANS
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "GLSL.h"

void glfwErrorCallback(int error, const char* description)
{
    std::cerr << "GLFW ERROR: " << description << std::endl;
}

/**
 * main entry function - Establishes the OpenGL context with the GLFW
 * (http://www.glfw.org/) and creates a window within this context.
 *
 * 
 */
int main(void)
{
    // Initialize the GLFW library
    if ( !glfwInit() )
        exit(EXIT_FAILURE);

    // Request a specific OpenGL context when the window is created
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwSetErrorCallback( glfwErrorCallback );
        
    /* Create a windowed mode window and its OpenGL context */
    int winWidth = 800;
    float aspectRatio = 9.0 / 16.0; // winWidth / (float)winHeight;
    int winHeight = winWidth * aspectRatio;
    
    GLFWwindow* window = glfwCreateWindow(winWidth, winHeight, "OpenGL Example", NULL, NULL);
    if (!window) {
        std::cerr << "ERROR: GLFW did not create a window!" << std::endl;
        
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
	
	glewExperimental=true;
	glewInit();

    const GLubyte* renderer = glGetString (GL_RENDERER);
    const GLubyte* version = glGetString (GL_VERSION);
    std::cout << "Renderer: " << renderer << std::endl;
    std::cout << "OpenGL version supported: " << version << std::endl;
    std::cout << "GLFW Version String: " << glfwGetVersionString() << std::endl;
    GLint major_version, minor_version, max_texture_size;
    GLboolean depth_test;
    glGetIntegerv(GL_MAJOR_VERSION, &major_version);
    std::cout << "OpenGL Major Version: " << major_version << std::endl;
    glGetIntegerv(GL_MINOR_VERSION, &minor_version);
    std::cout << "OpenGL Minor Version: " << minor_version << std::endl;
    glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_texture_size);
    std::cout << "OpenGL Max Texture Size: " << max_texture_size << std::endl;
    glGetBooleanv(GL_DEPTH_TEST, &depth_test);
    std::cout << "Depth test active: ";
    if(depth_test) std::cout << "true" << std::endl;
    else std::cout << "false" << std::endl;

    // Need to tell OpenGL how big the window is going to be so it can
    // create enough memory on the graphics card to store the pixel
    // colors.
    //
    // We will query glfw to see how big the window was when we
    // created it and then pass that info to OpenGL's viewport function.
    int fb_width, fb_height;
    glfwGetFramebufferSize(window, &fb_width, &fb_height);
    glViewport(0, 0, fb_width, fb_height);

    // Set the background color for our window
    glClearColor(0.4, 0.4, 0.4, 1.0);

	double start_time, end_time;

	GLuint m_triangleVBO;
	glGenBuffers(1, &m_triangleVBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);

	int numFloatsNeeded = 3 * 8;
	float* host_VertexBuffer = new float[ numFloatsNeeded ];

	//Get Texture Images
	std::string texFilename = "textureMapCalibration_1024x1024.png";
	std::cout << "Reading texture map data from file: " << texFilename << std::endl;
	png::image< png::rgb_pixel > texPNGImage;
	texPNGImage.read( texFilename );
	int pngWidth = texPNGImage.get_width();
	int pngHeight = texPNGImage.get_height();
	float *copiedPNGData = new float[ pngHeight * pngWidth * 3 ];
	
	int tIdx = 0;
	for (unsigned int idx=0; idx<pngHeight*pngWidth; ++idx) {
		size_t col = idx % pngWidth;
		size_t row = static_cast<size_t>( floor(idx / static_cast<float>(pngWidth)) );
 
		png::rgb_pixel texel = texPNGImage[ pngHeight-1 - row ][col];
 
		copiedPNGData[tIdx++] = texel.red/255.0;
		copiedPNGData[tIdx++] = texel.green/255.0;
		copiedPNGData[tIdx++] = texel.blue/255.0;
	} 
	//Add textures to glTextures
	GLuint texID;
	glGenTextures(1, &texID);

	glBindTexture(GL_TEXTURE_2D, texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pngWidth, pngHeight, 0, GL_RGB, GL_FLOAT, copiedPNGData);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete [] copiedPNGData;

	tIdx = 0;

	// V0
	host_VertexBuffer[ tIdx++ ] = 0.0f; //COORDS
	host_VertexBuffer[ tIdx++ ] = 2.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f; //NORMAL
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 1.0f;
	host_VertexBuffer[ tIdx++ ] = 0.5f; //TextureMap
	host_VertexBuffer[ tIdx++ ] = 1.0f;

	// V1
	host_VertexBuffer[ tIdx++ ] = -1.0f; //COORDS
	host_VertexBuffer[ tIdx++ ] = -2.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f; //NORMAL
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 1.0f;
	host_VertexBuffer[ tIdx++ ] = 1.0f; //TextureMap
	host_VertexBuffer[ tIdx++ ] = 0.0f;

	// V2
	host_VertexBuffer[ tIdx++ ] = 1.0f; //COORDS
	host_VertexBuffer[ tIdx++ ] = -2.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f; //NORMAL
	host_VertexBuffer[ tIdx++ ] = 0.0f;
	host_VertexBuffer[ tIdx++ ] = 1.0f;
	host_VertexBuffer[ tIdx++ ] = 0.0f; //TextureMap
	host_VertexBuffer[ tIdx++ ] = 0.0f;

	int numBytes = (numFloatsNeeded) * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, numBytes, host_VertexBuffer, GL_STATIC_DRAW);
	delete [] host_VertexBuffer;

	GLuint m_VAO;
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	glEnableVertexAttribArray(0);  // enable attrib 0
	glEnableVertexAttribArray(1);  // enable attrib 1
	glEnableVertexAttribArray(2);  // enable attrib 2

	glBindBuffer(GL_ARRAY_BUFFER, m_triangleVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0); //Location
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *)12); // Color
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid *)24); // Color
	

	glBindVertexArray(0);

	sivelab::GLSLObject shader;
	shader.addShader( "vertexShader_perVertexColor.glsl", sivelab::GLSLObject::VERTEX_SHADER );
	shader.addShader( "fragmentShader_vertexColorBlend.glsl", sivelab::GLSLObject::FRAGMENT_SHADER );
	shader.createProgram();

	GLint projMatrixID = shader.createUniform("projMatrix");
	GLint viewMatrixID = shader.createUniform("viewMatrix");
	GLint modelMatrixID = shader.createUniform("modelMatrix");

	Camera cam("Perspective", sivelab::Vector3D(5,0,-5), sivelab::Vector3D(-1,0,1), 1.0, 0.5, 250, 250);
	
	glm::mat4 modelTransform;

	GLuint texUnitID;

    // Loop until the user closes the window 
   while (!glfwWindowShouldClose(window))
    {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.activate();

		if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS)
            cam.setPosition(cam.getPosition() - cam.getW());
		if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS)
            cam.setPosition(cam.getPosition() + cam.getW());
		if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS)
            cam.setPosition(cam.getPosition() - cam.getU());
		if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS)
            cam.setPosition(cam.getPosition() + cam.getU());

		glUniformMatrix4fv(projMatrixID, 1, GL_FALSE, glm::value_ptr( cam.getProjectionMatrix() ));
		glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr( cam.getViewMatrix() ));
		glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr( modelTransform ));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texID);
		glUniform1i(texUnitID, 0);

		glBindVertexArray(m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		shader.deactivate();
	start_time = glfwGetTime();
        // Clear the window's buffer (or clear the screen to our
        // background color)

        //
        // Eventually, any OpenGL code that renders your scene can go here
        // 

        // Swap the front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process any events that may have occured with
        // the mouse or keyboard 
        glfwPollEvents();
        if (glfwGetKey( window, GLFW_KEY_ESCAPE ) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, 1);
		end_time = glfwGetTime();
		if (glfwGetKey( window, GLFW_KEY_T ) == GLFW_PRESS)
	    	std::cout << "Frame Rate: " << (1/(end_time - start_time)) << std::endl;
    } 

    // Terminate the application, close the window and clean-up any
    // OpenGL context memory
    glfwTerminate();
    
    exit(EXIT_SUCCESS);
}

