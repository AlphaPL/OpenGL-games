// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.
#include<iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 Control::ViewMatrix;
bool Control::inGame = true;
glm::mat4 Control::ProjectionMatrix;

glm::mat4 Control::getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 Control::getProjectionMatrix(){
	return ProjectionMatrix;
}


glm::vec3 position = glm::vec3( 0, 0, 100 ); 
float horizontalAngle = 0.0f;
float verticalAngle = 0.0f;
float initialFoV = 45.0f;
float speed = 80.0f;
float mouseSpeed = 0.005f;



void Control::computeMatricesFromInputs(vec3& monkeyPos){

	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	glfwSetCursorPos(window, 1024/2, 768/2);

	horizontalAngle += xpos - 1024/2 ;
	verticalAngle   += ypos - 768/2;

	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	glm::vec3 right = glm::vec3(
		1, 
		0,
		0
	);
	
	glm::vec3 up = glm::cross( right, direction );

	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += vec3(0,0,-1) * deltaTime * speed;
	}
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= vec3(0,0,-1) * deltaTime * speed;
	}
	if(position.x < 85.0)
		if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
			monkeyPos += right * deltaTime * speed;
		}
	if(position.x > - 85.0)
		if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
			monkeyPos -= right * deltaTime * speed;
		}
	float FoV = initialFoV;
	Control::ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 200000.0f);
	Control::ViewMatrix       = glm::lookAt(
								position,           
								vec3(0,0,0), 
								vec3(0,1,0)                  
						   );
	Control::ViewMatrix = Control::ViewMatrix * glm::rotate(mat4(1.0f), verticalAngle, vec3(1,0,0)) * glm::rotate(mat4(1.0f), horizontalAngle, vec3(0,1,0));

	lastTime = currentTime;
}
