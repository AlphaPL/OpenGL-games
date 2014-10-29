#include"HelpfulFuncs.hpp"
#include"Background.hpp"

GLFWwindow* window;



int main( void )
{
	std::srand(time(0));

	if(init(window))
		return -1;

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders


	// Get a handle for our "MVP" uniform


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
	// Or, for an ortho camera :
	//glm::mat4 Projection = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
	
	// Camera matrix
	glm::mat4 View       = glm::lookAt(
								glm::vec3(0,0,12), // Camera is at (4,3,3), in World Space
								glm::vec3(0,0,0), // and looks at the origin
								glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
						   );
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model      = glm::mat4(1.0f);
	// Our ModelViewProjection : multiplication of our 3 matrices
	glm::mat4 MVP        = Projection * View * Model; // Remember, matrix multiplication is the other way around

	// Load Textures and shaders

	

	GLuint TextureShaders = LoadShaders( "SimpleTransform.vertexshader", "SingleColor.fragmentshader" );
	GLuint MatrixID = glGetUniformLocation(TextureShaders, "MVP");
	GLuint ColorShaders = LoadShaders( "TransformVertexShader.vertexshader", "ColorFragmentShader.fragmentshader" );
			Background back;
	GLuint TextureID  = glGetUniformLocation(TextureShaders, "myTextureSampler");


	// Setup buffers and 2D text 

	initText2D( "Holstein.DDS" );


	
	


	float camManip=-200;

	bool fadeout = false;
	bool game = false;
	do{

		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		if(!game)
		{
			if(camManip<0 && !fadeout)
			{
				camManip +=0.5;
				View       = glm::lookAt(
										glm::vec3(camManip,0,45), // Camera is at (4,3,3), in World Space
										glm::vec3(0,0,70), // and looks at the origin
										glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
								   );
			}
			else
			{
				if(camManip>6.28)
					camManip=0.1;
				if(!fadeout)
				camManip += 0.01;
				else
					if(camManip>0)
						camManip-=0.01;
					else
					{
						game = true;
						camManip = 3.14;
					}
				View       = glm::lookAt(
										glm::vec3(sin(camManip*2)*7,-sin(camManip)*7,45), // Camera is at (4,3,3), in World Space
										glm::vec3(0,0,70), // and looks at the origin
										glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
										);
				if(glfwGetKey( window, GLFW_KEY_SPACE))
					fadeout=true;
			}
		}
		else
		{
							
							View   = glm::lookAt(
										glm::vec3(0,0,45), // Camera is at (4,3,3), in World Space
										glm::vec3(0,0,0), // and looks at the origin
										glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
								   );
		}

	

		// Drawing and rotations


		// Draw table background


		back.draw(MVP,Projection,View, Model, TextureShaders, MatrixID, TextureID);

	
		// Draw Text

		if(camManip>0)
			printText2D("Press any button to start", 30, 100, 30);
		// Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteProgram(TextureShaders);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	cleanupText2D();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}