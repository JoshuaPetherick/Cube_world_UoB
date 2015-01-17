// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;

// Include Cube Creator
#include <src/Cube.hpp>

int main( void )
{
	int height, width;

	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Finds the primary monitors screen size
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//Sets the height and width to main monitors screen size
	height = mode->height;
	 width = mode->width;

	// Open a window and create its OpenGL context, uses height and width so that it doesn't break the resolution when going into full screen mode
	window = glfwCreateWindow( width, height, "Joshua's Cube World", glfwGetPrimaryMonitor(), NULL);

	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Ensure we can capture the escape key being pressed
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	//Hides the mouse cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	// Light blue background
	glClearColor(0.6f, 1.0f, 1.0f, 0.1f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);

	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	// Cull triangles which normally is not towards the camera
	glEnable(GL_CULL_FACE);
	
	Cube draw;
	draw.init();

	do{	
		draw.setupDraw(window);	 
		draw.drawGround(20, 30); //Goes X then Z length. 
		draw.drawHouse(7, 9);    //Goes X then Z length. Should be odd and both values greater than or equal to 5
		draw.update(window);

	} // Check if the ESC key was pressed, closes window is true
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO
	draw.close();

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

