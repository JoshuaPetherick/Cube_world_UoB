
#include "camera.hpp"

using namespace glm;

mat4 ViewMatrix;
mat4 ProjectionMatrix;

mat4 getViewMatrix(){
	return ViewMatrix;
}
mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}

// Starting position of the camera
glm::vec3 position = glm::vec3( 0, 2, 0 ); 
// Starting horizontal angle, should be toward -Z
float horizontalAngle = 3.14f;
// Staring vertical angle, should be 0
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

void cameraControls(GLFWwindow* window){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);
	
	//Finds the primary monitors screen size
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	//Sets the height and width to main monitors screen size
	int height = mode->height;
	int width = mode->width;

	// Gets mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Resets mouse position, for next frame, in the center of the screen
	glfwSetCursorPos(window, height/2, width/2);

	// Compute new orientation from mouse input
	horizontalAngle += mouseSpeed/2 * float(height/2 - xpos );
	verticalAngle   += mouseSpeed/2 * float( width/2 - ypos );

	// Stops the camera from going upside down
	if( verticalAngle < -0.9 )
	{
		verticalAngle = -0.9;
	}
	else if( verticalAngle > 0.9 )
	{
		verticalAngle = 0.9;
	}

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);	

	// Right vector
	vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Move right
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Sprint forward
	if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS && glfwGetKey( window, GLFW_KEY_LEFT_SHIFT ) == GLFW_PRESS){
		position += direction * deltaTime * 6.0f;
	}

	float FoV = initialFoV;

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
		position,           // Camera is here
		position+direction, // and looks here : at the same position, plus "direction"
		up                  // Head is up
				   );

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
