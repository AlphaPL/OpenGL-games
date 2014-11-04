#ifndef BALL_HPP
#define BALL_HPP


#include<vector>
#include "HelpfulFuncs.hpp"
#include "Ball.hpp"
#include <objloader.hpp>
class Ball
{

public:


	GLuint vertexbuffer;
	GLfloat x;
	GLfloat y;
	GLfloat xspeed;
	GLfloat yspeed;
	GLint size;
	void draw(mat4 MVP,mat4 Projection, mat4 View, mat4 Model, GLint TextureShaders , GLint MatrixID , GLint TextureID, GLint ColorShaders)
	{
		MVP = Projection * View * glm::translate(mat4(1.0f),vec3(x,y,0.125))* glm::scale(mat4(1.0f), vec3(0.125,0.125,0.125)) * glm::rotate(mat4(1.0f), (x/2.2f)*90.0f,vec3(0,1,0)) *glm::rotate(mat4(1.0f), (y/2.3f)*-360.0f,vec3(1,0,0))* Model ;
		DrawWithoutTexture(ColorShaders, MatrixID, MVP, vertexbuffer, vertexbuffer, size);
	}

	Ball()
	{
		yspeed = 0;
		xspeed = 0;
		x=0;
		y=-1.1875;

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("ball.obj", vertices, uvs, normals);

	// Load it into a VBO

	size = vertices.size();
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


	}

	void moveLeft()
	{
		if(x>-2.1)
		x-=0.04;
	}

	void moveRight()
	{
		if(x<2.1)
		x+=0.04;
	}

	void proceed()
	{
		if(x<-2.3 || x>2.3)
			xspeed = -xspeed;

		if(y>1.8)
			yspeed = -yspeed;

		x+=xspeed;
		y+=yspeed;
	}



};

#endif