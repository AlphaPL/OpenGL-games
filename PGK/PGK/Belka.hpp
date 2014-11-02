#ifndef BELKA_HPP
#define BELKA_HPP
#include "HelpfulFuncs.hpp"
#include "Ball.hpp"
class Belka
{

public:

	GLint logo_buffer;
	GLint endings;
	GLint logo_border_buffer;
	GLuint uvbuffer;
	GLuint logo;
	GLuint logo_back;

	GLfloat x;
	GLfloat y;
	void draw(mat4 MVP,mat4 Projection, mat4 View, mat4 Model, GLint TextureShaders , GLint MatrixID , GLint TextureID)
	{
		MVP = Projection * View * glm::translate(mat4(1.0f),vec3(x,y,0))* glm::scale(mat4(1.0f), vec3(0.15,0.05,0.2)) * Model ;
		DrawWithTexture(TextureShaders, MatrixID, MVP, logo_buffer, uvbuffer, logo, TextureID,24);

	}

	Belka()
	{
		x=0;
		y=-1.3;

		logo = loadBMP_custom("belka_center.bmp");

		GLfloat buffer_data_for_logo[] = { 
		-2, 0, 0.0f,
		2, 0,0.0f,
		 2,  1, 0.0f,
		 -2, 0, 0.0f,
		-2, 1, 0.0f,
		 2,  1, 0.0f,

		 -2, 0, 0.0f,
		2, 0,0.0f,
		2, 0,1.0f,
		-2, 1,0.0f,
		2, 1,0.0f,
		2, 1,1.0f,

		-2, 0, 0.0f,
		-2, 0,1.0f,
		2, 0,1.0f,
		-2, 1, 0.0f,
		-2, 1,1.0f,
		2, 1,1.0f,

		-2, 0, 1.0f,
		2, 0,1.0f,
		 2,  1, 1.0f,
		 -2, 0,1.0f,
		-2, 1, 1.0f,
		 2,  1, 1.0f,

		};

		logo_buffer = genBuffer(buffer_data_for_logo,sizeof(buffer_data_for_logo));

		static const GLfloat uv_data_for_table[] = { 
			0, 0,
			1, 0,
			1, 1,
			0, 0,
			0, 1,
			1, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 0,
			1, 0,
			1, 1,

			0, 0,
			0, 1,
			1, 1,
			0, 0,
			0, 1,
			1, 1,

			0, 0,
			1, 0,
			1, 1,
			0, 0,
			0, 1,
			1, 1,

		};

		uvbuffer  = genBuffer((GLfloat*)uv_data_for_table, sizeof(uv_data_for_table));
	}

	void moveLeft()
	{
		if(x>-2.2)
		x-=0.04;
	}

	void moveRight()
	{
		if(x<2.2)
		x+=0.04;
	}

	void collision(Ball& ball)
	{
		if(abs(ball.y-y) < 0.05 && abs(ball.x-x) < 0.3)
		{
			ball.yspeed = -ball.yspeed;
			ball.xspeed = (ball.x-x)*0.2;
		}
	}

};

#endif