#include "Cube.h"
extern bool game;
GLFWwindow* window;
extern vec3 position;
int main( void )
{
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

	// Open a window and create its OpenGL context
	window = glfwCreateWindow( 1024, 768, "Tutorial 08 - Basic Shading", NULL, NULL);
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

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);
	// Cull triangles which normal is not towards the camera

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders


	Sphere sphere("ball.obj", "Sphere.vertexshader", "Sphere.fragmentshader", vec3(1, 0, 0) );

	Sphere monkey("suzanne.obj",  "StandardShading.vertexshader", "StandardShading.fragmentshader", vec3(0, 1, 0) );
	monkey.pos = glm::vec3( 0, -2, 4 );
	Cube cube("cube.obj",  "StandardShading.vertexshader", "StandardShading.fragmentshader", vec3(0.75, 0.75, 1) );

	// Get a handle for our "LightPosition" uniform
	

	do{

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Compute the MVP matrix from keyboard and mouse input
		computeMatricesFromInputs(monkey.pos);

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform

		glm::vec3 lightPos = vec3(0, 30, 2);
		sphere.move();
		sphere.draw(getProjectionMatrix(), getViewMatrix(), lightPos, position);
		monkey.changeModel(monkey.pos, 20.0f);
		monkey.draw(getProjectionMatrix(), getViewMatrix(), lightPos, position);
		cube.draw(getProjectionMatrix(), getViewMatrix(), lightPos, position);
		sphere.collision(monkey);
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 && game);

	// Cleanup VBO and shader

	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

