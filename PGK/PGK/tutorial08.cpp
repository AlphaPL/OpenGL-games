#include "Cube.h"
#include "controls.hpp"
GLFWwindow* window;
extern vec3 position;
int main( void )
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow( 1024, 768, "Tutorial 08 - Basic Shading", NULL, NULL);
	if( window == NULL ){
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// For the next frame, the "last time" will be "now"
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetCursorPos(window, 1024/2, 768/2);

	glClearColor(0.3f, 0.7f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); 
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);



	Sphere sphere("ball.obj", "Sphere.vertexshader", "Sphere.fragmentshader", vec3(1, 0, 0) );

	Sphere monkey("suzanne.obj",  "StandardShading.vertexshader", "StandardShading.fragmentshader", vec3(0, 1, 0) );
	monkey.pos = glm::vec3( 0, -2, 4 );
	Cube cube("cube.obj",  "StandardShading.vertexshader", "StandardShading.fragmentshader", vec3(1, 1, 1) );


	

	do{


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



		Control::computeMatricesFromInputs(monkey.pos);


		glDisable(GL_BLEND);
		glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glm::vec3 lightPos = vec3(50, 0, -300);
		sphere.move();
		monkey.changeModel(monkey.pos, 20.0f, 180.0f);
		cube.draw(Control::getProjectionMatrix(), Control::getViewMatrix(), lightPos, position);
		monkey.draw(Control::getProjectionMatrix(), Control::getViewMatrix(), lightPos, position);
		cube.draw(Control::getProjectionMatrix(),Control::getViewMatrix(), lightPos, position);
		sphere.collision(monkey);	


		glDisable(GL_CULL_FACE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		sphere.sort(Control::getViewMatrix());
		sphere.draw(Control::getProjectionMatrix(), Control::getViewMatrix(), lightPos, position);



		glfwSwapBuffers(window);
		glfwPollEvents();

	} 
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 && Control::inGame);


	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}

