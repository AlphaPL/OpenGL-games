#ifndef HELP_HPP
#define HELP_HPP

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <GL/glew.h>
#include <time.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

GLint genBuffer(const GLfloat* buffer_data, int size)
{
	GLuint buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, size, buffer_data, GL_STATIC_DRAW);

	return buffer;
}

int init(GLFWwindow*& window)
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

	return 0;
}

void startAnimation(mat4& View, float& camManip, bool& fadeout, bool& game, GLFWwindow*& window)
{
			if(camManip<0 && !fadeout)
			{
				camManip +=0.5;
				View       = glm::lookAt(
										glm::vec3(camManip,0,25), // Camera is at (4,3,3), in World Space
										glm::vec3(0,0,0), // and looks at the origin
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
						camManip = 25;
					}
				View       = glm::lookAt(
										glm::vec3(sin(camManip*2)*7,-sin(camManip)*7,25), // Camera is at (4,3,3), in World Space
										glm::vec3(0,0,0), // and looks at the origin
										glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
										);
				if(glfwGetKey( window, GLFW_KEY_SPACE))
					fadeout=true;
			}
};

#endif