// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
// Include GLEW
#include <GL/glew.h>
#include <time.h>
// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;
using namespace std;
#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <text2D.hpp>

void DrawWithTexture(GLuint TextureShaders, GLuint MatrixID, glm::mat4 MVP, GLuint vertexbuffer, 	GLuint uvbuffer, GLuint TableTex ,	GLuint TextureID, int howmany)
{

	
		// Use our shader
		glUseProgram(TextureShaders);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

				// Bind our texture in Texture Unit 0
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TableTex);
		// Set our "myTextureSampler" sampler to user Texture Unit 0
		glUniform1i(TextureID, 0);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, howmany); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}


void DrawWithoutTexture(GLuint TextureShaders, GLuint MatrixID, glm::mat4 MVP, GLuint vertexbuffer, 	GLuint uvbuffer, int howmany)
{

	
		// Use our shader
		glUseProgram(TextureShaders);
		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_TRIANGLES, 0, howmany); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
}

int main( void )
{
	std::srand(time(0));
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
	window = glfwCreateWindow( 1024, 768, "Match Two game", NULL, NULL);
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

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders


	// Get a handle for our "MVP" uniform


	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
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

	GLuint TableTex = loadBMP_custom("uvtemplate.bmp");
	GLuint Kolo = loadBMP_custom("kolo.bmp");
	GLuint Krzyz = loadBMP_custom("krzyzyk.bmp");
	GLuint Gwiazdka = loadBMP_custom("gwiazdka.bmp");
	GLuint Fale = loadBMP_custom("fale.bmp");
	GLuint Diamond = loadBMP_custom("diamond.bmp");
	GLuint Strzalka = loadBMP_custom("strzalka.bmp");
	GLuint Triangle = loadBMP_custom("triangle.bmp");
	GLuint Serce = loadBMP_custom("serducho.bmp");
	GLuint Background = loadBMP_custom("background.bmp");
	GLuint Border = loadBMP_custom("border.bmp");
	GLuint TextureID  = glGetUniformLocation(TextureShaders, "myTextureSampler");

	// Initialise location and coordinates arrays

	static const GLfloat buffer_data_for_table[] = { 
		-5.5f, -4.1f, -1.5f,
		5.5f, -4.1f,-1.5f,
		 5.5f,  4.1f, -1.5f,
		 -5.5f, -4.1f, -1.5f,
		-5.5f, 4.1f, -1.5f,
		 5.5f,  4.1f, -1.5f,
	};

	static const vec3 translations_card[] = {
		vec3(-4.0,3.5,0.0f),
		vec3(-1.5f,3.5,0.0f),
		vec3(1.5f,3.5,0.0f),
		vec3(4.0,3.5,0.0f),
		vec3(-4.0,1.5,0.0f),
		vec3(-1.5f,1.5,0.0f),
		vec3(1.5f,1.5,0.0f),
		vec3(4.0,1.5,0.0f),
		vec3(-4.0,-1.5,0.0f),
		vec3(-1.5f,-1.5,0.0f),
		vec3(1.5f,-1.5,0.0f),
		vec3(4.0,-1.5,0.0f),
		vec3(-4.0,-3.5,0.0f),
		vec3(-1.5f,-3.5,0.0f),
		vec3(1.5f,-3.5,0.0f),
		vec3(4.0,-3.5,0.0f),
	};

	static const vec3 translations_arrow[] = {
		vec3(-4.0,2.25,0.0f),
		vec3(-1.5f,2.25,0.0f),
		vec3(1.5f,2.25,0.0f),
		vec3(4.0,2.25,0.0f),
		vec3(-4.0,0.25,0.0f),
		vec3(-1.5f,0.25,0.0f),
		vec3(1.5f,0.25,0.0f),
		vec3(4.0,0.25,0.0f),
		vec3(-4.0,-2.75,0.0f),
		vec3(-1.5f,-2.75,0.0f),
		vec3(1.5f,-2.75,0.0f),
		vec3(4.0,-2.75,0.0f),
		vec3(-4.0,-4.75,0.0f),
		vec3(-1.5f,-4.75,0.0f),
		vec3(1.5f,-4.75,0.0f),
		vec3(4.0,-4.75,0.0f),
	};

	static GLfloat rotations[] = {
	    180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
		180.0f,
	};

	static GLuint cardTextures[] = {
		Kolo,
		Krzyz,
		Gwiazdka,
		Fale,
		Diamond,
		Strzalka,
		Triangle,
		Serce,
		Kolo,
		Krzyz,
		Gwiazdka,
		Fale,
		Diamond,
		Strzalka,
		Triangle,
		Serce,
	};


	static const GLfloat g_vertex_buffer_color_data[] = { 
		0.583f,  0.771f,  0.014f,
		0.609f,  0.115f,  0.436f,
		0.327f,  0.483f,  0.844f,
	};

	static const GLfloat buffer_data_for_card[] = { 
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
	};

	static const GLfloat buffer_data_for_card_border[] = { 
		-0.5f, -0.5f, -0.1f,
		-0.5f, 0.5f, -0.0f,
		-0.5f, 0.5f, -0.1f,
		-0.5f, -0.5f, -0.0f,
		-0.5f, -0.5f, -0.1f,
		-0.5f, 0.5f, -0.0f,
		0.5f, -0.5f, -0.1f,
		0.5f, 0.5f, -0.0f,
		0.5f, 0.5f, -0.1f,
		0.5f, -0.5f, -0.0f,
		0.5f, -0.5f, -0.1f,
		0.5f, 0.5f, -0.0f,
		-0.5f, 0.5f, -0.1f,
		0.5f, 0.5f,  -0.0f,
		0.5f, 0.5f,  -0.1f,
		-0.5f, 0.5f, -0.0f,
		-0.5f, 0.5f,  -0.1f,
	     0.5f,0.5f,  -0.0f,
		 -0.5f, -0.5f,  -0.1f,
		0.5f, -0.5f,  -0.0f,
		0.5f, -0.5f,  -0.1f,
		-0.5f, -0.5f,  -0.0f,
		-0.5f, -0.5f,  -0.1f,
		0.5f, -0.5f,  -0.0f,
	};

	static const GLfloat buffer_data_for_card_back[] = { 
		-0.5f, -0.5f, -0.1f,
		-0.5f, 0.5f, -0.1f,
		0.5f, 0.5f, -0.1f,
		-0.5f, -0.5f, -0.1f,
		0.5f, -0.5f,-0.1f,
		0.5f, 0.5f,-0.1f,
	};

	static const GLfloat color_buffer_for_cards[] = { 
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
		1.0f,  0.0f,  0.0f,
	};


	static const GLfloat buffer_data_for_arrow[] = { 
		-0.0f, -0.0f, -0.0f,
		-0.5f, 0.0f, -0.0f,
		0.0f, 0.5f, -0.0f,
		-0.0f, -0.0f, -0.0f,
		0.5f, 0.0f, -0.0f,
		0.0f, 0.5f, -0.0f,
	};
	
	// Two UV coordinatesfor each vertex. They were created withe Blender.
	static const GLfloat uv_data_for_table[] = { 
		0, 0,
		0, 1,
		1, 1,
		0, 0,
		1, 0,
		1, 1,
	};


	// setup logic control variables

	bool draw[16];
	int arrow_location = 0;
	bool up_released = false;
	bool down_released = false;
	bool right_released = false;
	bool left_released = false;
	bool space_released = false;
	bool rotation = false;
	bool start = true;
	int howManyGuesses = 8;
	int rotationID1 = -1;
	int rotationID2 = -1;
	bool rotationOut = false;
	int howManyFalseGuesses = 0;


	// Setup buffers and 2D text 

	initText2D( "Holstein.DDS" );

	GLuint vertexbuffer[5];
	glGenBuffers(5, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_for_table), buffer_data_for_table, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_for_card), buffer_data_for_card, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_for_card), buffer_data_for_card_back, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_for_card_border), buffer_data_for_card_border, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data_for_arrow), buffer_data_for_arrow, GL_STATIC_DRAW);

	GLuint uvbuffer;
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uv_data_for_table), uv_data_for_table, GL_STATIC_DRAW);

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer_for_cards), color_buffer_for_cards, GL_STATIC_DRAW);
	

	
	do{

		// logic

		if(start)
		{
			random_shuffle(cardTextures,cardTextures+16);
			for (int i=0;i<16;i++)
			{
				draw[i] = true;
				rotations[i] = 180.0f;
			}
			howManyFalseGuesses = 0;
			start = false;

		}
		if(!rotation && !rotationOut)
		{
			if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS && arrow_location>3 &&  up_released)
			{
				arrow_location -= 4; up_released = false; 
			}

			if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS && arrow_location< 12 && down_released)
			{
				arrow_location += 4; down_released = false;

			}

			if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS && arrow_location % 4 !=0 && left_released)
			{
				arrow_location -= 1; left_released = false;
			}

			if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS && arrow_location % 4 !=3 && right_released)
			{
				arrow_location += 1; right_released = false;
			}

			if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_RELEASE){
				up_released = true;
			}

			if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_RELEASE){
				down_released = true;
			}

			if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_RELEASE){
				right_released = true;
			}

			if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_RELEASE){
				left_released = true;
			}

			if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_PRESS && !rotation && space_released && arrow_location != rotationID1 && draw[arrow_location])
			{
				space_released = false;
				rotation = true;
				if(rotationID1 == -1)
					rotationID1 = arrow_location;
				else if(rotationID2 == -1)
					rotationID2 = arrow_location;
			}

			if (glfwGetKey( window, GLFW_KEY_SPACE) == GLFW_RELEASE && !rotation)
			{
				space_released = true;
			}
		}

		// Drawing and rotations


		// Draw table background
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		MVP = Projection * View * Model* glm::scale(glm::vec3(2.0f, 2.0f ,2.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, vertexbuffer[0], uvbuffer, TableTex, TextureID,6);

		// Draw cards
		for (int i=0;i<16;i++)
		if(draw[i])
		{
			if(rotation)
			{
				if(rotationID1 == i && rotationID2 == -1)
					if(rotations[i] != 0)
						rotations[i] -= 5;
					else
						rotation = false;
				if(rotationID2 == i)
					if(rotations[i] != 0)
						rotations[i] -= 5;
					else if(cardTextures[rotationID1] == cardTextures[rotationID2])
					{
						draw[rotationID1] = false;
						draw[rotationID2] = false;
						rotationOut = true; rotation = false;
						howManyGuesses -= 1;
						if(howManyGuesses == 0)
							start = true;
					}
					else if (cardTextures[rotationID1] != cardTextures[rotationID2])
					{
						rotationOut = true; rotation = false; howManyFalseGuesses++;
					}
			}
			else if(rotationOut)
			{
					if(rotations[rotationID1] != 180)
					{
						rotations[rotationID1] += 2;
						rotations[rotationID2] += 2;
					}
					else
					{
						rotationOut = false;
						rotationID1 = -1;
						rotationID2 = -1;
					}
			}
			MVP = Projection * View * glm::translate(mat4(1.0f),translations_card[i]) * glm::rotate(mat4(1.0f), rotations[i], vec3(0,1,0));
			DrawWithTexture(TextureShaders, MatrixID, MVP, vertexbuffer[1], uvbuffer, cardTextures[i], TextureID,6);
			DrawWithTexture(TextureShaders, MatrixID, MVP, vertexbuffer[2], uvbuffer, Background, TextureID,6);
			DrawWithTexture(TextureShaders, MatrixID, MVP, vertexbuffer[3], uvbuffer, Border, TextureID,24);
		}

		//Draw arrow
		MVP = Projection * View * Model* glm::translate(mat4(1.0f), translations_arrow[arrow_location]);
		DrawWithoutTexture(ColorShaders, MatrixID, MVP, vertexbuffer[4], colorbuffer, 6);

		// Draw Text
		char text[256];
		sprintf(text,"Ilosc przegran : %d ", howManyFalseGuesses );
		printText2D(text, 0, 0, 30);


		// Swap Buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
		   glfwWindowShouldClose(window) == 0 );

	// Cleanup VBO and shader
	glDeleteBuffers(5, vertexbuffer);
	glDeleteBuffers(1, &colorbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(TextureShaders);
	glDeleteTextures(1, &TextureID);
	glDeleteVertexArrays(1, &VertexArrayID);
	cleanupText2D();
	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}