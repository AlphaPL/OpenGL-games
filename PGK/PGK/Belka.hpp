#ifndef BELKA_HPP
#define BELKA_HPP
#include "HelpfulFuncs.hpp"
class Belka
{

public:

	GLint logo_buffer;
	GLint logo_border_buffer;
	GLuint uvbuffer;
	GLuint logo;
	GLuint logo_back;

	GLfloat x;
	GLfloat y;
	void draw(mat4 MVP,mat4 Projection, mat4 View, mat4 Model, GLint TextureShaders , GLint MatrixID , GLint TextureID)
	{
		MVP = Projection * View *  Model ;
		DrawWithTexture(TextureShaders, MatrixID, MVP, logo_buffer, uvbuffer, logo, TextureID,24);

	}

	Belka()
	{
		x=0;
		y=-0.5;

		logo = loadBMP_custom("belka_center.bmp");


		GLfloat buffer_data_for_logo[] = { 
		-.05f, -.01f, 3.5f,
		.05f, -.01f,3.5f,
		 .05f,  .01f, 3.5f,
		 -.05f, -.01f, 3.5f,
		-.05f, .01f, 3.5f,
		 .05f,  .01f, 3.5f,

		 -.05f, -.01f, 3.5f,
		.05f, -.01f,3.5f,
		.05f, -.01f,1.5f,
		-.05f, .01f,-3.5f,
		.05f, .01f,3.5f,
		.05f, .01f,1.5f,

		-.05f, -.01f, 3.5f,
		-.05f, -.01f,1.5f,
		.05f, -.01f,1.5f,
		-.05f, .01f, 3.5f,
		-.05f, .01f,1.5f,
		.05f, .01f,1.5f,

		-.05f, -.01f, 1.5f,
		.05f, -.01f,1.5f,
		 .05f,  .01f, 1.5f,
		 -.05f, -.01f,1.5f,
		-.05f, .01f, 1.5f,
		 .05f,  .01f, 1.5f,
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
		if(x<57)
		x+=0.5;
	}

	void moveRight()
	{
		if(x>-57)
		x-=0.5;
	}

};

#endif