// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.
#include<iostream>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 200 ); 
// Initial horizontal angle : toward -Z
float horizontalAngle = 0.0f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 150.0f; // 3 units / second
float mouseSpeed = 0.005f;
bool game = true;

void computeMatricesFromInputs(vec3& monkeyPos){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += xpos - 1024/2 ;
	verticalAngle   += ypos - 768/2;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		1, 
		0,
		0
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += vec3(0,0,-1) * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= vec3(0,0,-1) * deltaTime * speed;
	}
	// Strafe right
	if(position.x < 85.0)
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
			monkeyPos += right * deltaTime * speed;
		}
	// Strafe left
	if(position.x > - 85.0)
		if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
			monkeyPos -= right * deltaTime * speed;
		}
	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 200000.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								vec3(0,0,0), // and looks here : at the same position, plus "direction"
								vec3(0,1,0)                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	ViewMatrix = ViewMatrix * glm::rotate(mat4(1.0f), verticalAngle, vec3(1,0,0)) * glm::rotate(mat4(1.0f), horizontalAngle, vec3(0,1,0));

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}
