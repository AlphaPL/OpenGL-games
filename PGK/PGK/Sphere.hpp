#ifndef SPHERE_HPP
#define SPHERE_HPP
// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <shader.hpp>
#include <texture.hpp>
#include <controls.hpp>
#include <objloader.hpp>
extern bool game;

class Sphere
{
	GLuint vertexbuffer;
	GLuint uvbuffer;
	GLuint normalbuffer;
	GLuint programID;


	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	float Scale;
    GLuint MatrixID;
	GLuint ViewMatrixID;
	GLuint ModelMatrixID;
	GLuint LightID;
	GLuint DiffuseColorID;
	vec3 diffuseColor;
	GLuint CamPositionID;
	vec3 ShiningColor;
	GLuint ShiningColorID;
	bool Shining;
	float level;
protected:
 glm::mat4 ModelMatrix;
	


	public:
		vec3 pos;
		Sphere(char textureToLoad[], char vertexShader[], char fragmentShader[], vec3 dcolor)
		{
			Shining = false;
			level = 6.0f;
			pos = vec3(RandomFloat(-80.0f, 80.0f),0,-1000.0f);
			ShiningColor = vec3(0,0,0);
			ModelMatrix = glm::mat4(1.0);
			diffuseColor = dcolor;
			programID = LoadShaders( vertexShader, fragmentShader);
		    loadOBJ(textureToLoad, vertices, uvs, normals);
			LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
			CamPositionID = glGetUniformLocation(programID, "postitionOfMonkey");
			DiffuseColorID = glGetUniformLocation(programID, "materialDiffuseColor");
			ShiningColorID = glGetUniformLocation(programID, "ShiningColor");
			glGenBuffers(1, &vertexbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

			glGenBuffers(1, &uvbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
			glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

			glGenBuffers(1, &normalbuffer);
			glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
			glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
		}

		void draw(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::vec3 lightPos, vec3 position)
		{
					glUseProgram(programID);

					glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);

					glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
					MatrixID = glGetUniformLocation(programID, "MVP");
				    ViewMatrixID = glGetUniformLocation(programID, "V");
				    ModelMatrixID = glGetUniformLocation(programID, "M");

					// Send our transformation to the currently bound shader, 
					// in the "MVP" uniform
					glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
					glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
					glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
					glUniform3f(DiffuseColorID, diffuseColor.x, diffuseColor.y, diffuseColor.z);
					glUniform3f(CamPositionID, position.x, position.y, position.z);
					glUniform3f(ShiningColorID, ShiningColor.x, ShiningColor.y, ShiningColor.z);
					// 1rst attribute buffer : vertices
					glEnableVertexAttribArray(0);
					glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
					glVertexAttribPointer(
						0,                  // attribute
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
						1,                                // attribute
						2,                                // size
						GL_FLOAT,                         // type
						GL_FALSE,                         // normalized?
						0,                                // stride
						(void*)0                          // array buffer offset
					);

					// 3rd attribute buffer : normals
					glEnableVertexAttribArray(2);
					glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
					glVertexAttribPointer(
						2,                                // attribute
						3,                                // size
						GL_FLOAT,                         // type
						GL_FALSE,                         // normalized?
						0,                                // stride
						(void*)0                          // array buffer offset
					);

					// Draw the triangles !
					glDrawArrays(GL_TRIANGLES, 0, vertices.size() );

					
					glDisableVertexAttribArray(0);
					glDisableVertexAttribArray(1);
					glDisableVertexAttribArray(2);
		}

		~Sphere()
		{
				glDeleteBuffers(1, &vertexbuffer);
				glDeleteBuffers(1, &uvbuffer);
				glDeleteBuffers(1, &normalbuffer);
		}

		void changeModel(glm::vec3 position, float scale = 1)
		{
			pos = position;
			ModelMatrix = glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f), position),180.0f, glm::vec3(0,1,0)), vec3(scale,scale,scale));
		}

		void reset()
		{
				pos.z = -1000.0f;
				level += 1.0f;
				pos.x = RandomFloat(-80.0f, 80.0f);
				Shining = RandomFloat(0.0, 1.0f) > 0.7f ? true : false;
				ShiningColor = Shining ? vec3(0,1,0) : vec3(0,0,0);
		}

		void move()
		{
			pos.z += level;
			if(pos.z > 0.0f)
			{
				reset();
			}
			changeModel(pos, -0.019*(pos.z)+20.0);
		}

		float RandomFloat(float min, float max)
		{
			float r = (float)rand() / (float)RAND_MAX;
			return min + r * (max - min);
		}

		void collision(Sphere& monkey)
		{
			if(abs(pos.x - monkey.pos.x) < 15.0f && abs(pos.z - monkey.pos.z) < 15.0f)
			{
				std::cout << "Collision!" << std::endl;
				if(Shining && level > 2.0f)
					level -= 3.0f;
				else
				{
				//	game = false;
				}
				reset();
			}
		}
};
#endif