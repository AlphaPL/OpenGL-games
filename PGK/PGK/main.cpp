#include "HelpfulFunc.hpp"
GLFWwindow* window;



int main( void )
{
	init(window);

	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);	
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,0,12), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	glm::mat4 Model      = glm::mat4(1.0f);
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	
	do{

	

		// Drawing and rotations


		// Draw table background
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		MVP = Projection * View * Model* glm::scale(glm::vec3(2.0f, 2.0f ,2.0f));

		// Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader

	cleanupText2D();
	glfwTerminate();

	return 0;
}