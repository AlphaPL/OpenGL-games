#ifndef TILE_HPP
#define TILE_HPP
#include "HelpfulFuncs.hpp"
#include "Ball.hpp"
class Tile
{

public:

	GLint logo_buffer;
	GLint endings;
	GLint logo_border_buffer;
	GLuint uvbuffer;
	GLuint logo;
	GLuint logo_back;
	bool alive;
	GLfloat x;
	GLfloat y;
	void draw(mat4 MVP,mat4 Projection, mat4 View, mat4 Model, GLint TextureShaders , GLint MatrixID , GLint TextureID)
	{
		if(alive)
		{
			MVP = Projection * View * glm::translate(mat4(1.0f),vec3(x,y,0))* glm::scale(mat4(1.0f), vec3(0.1,0.05,0.5)) * Model ;
			DrawWithTexture(TextureShaders, MatrixID, MVP, logo_buffer, uvbuffer, logo, TextureID,36);
		}
	}

	void collision(Ball& ball)
	{
		if(alive)
		{
			if( ( ( y - 0.05 > ball.y && y - 0.1 < ball.y)  ||  ( y + 0.05 < ball.y && y + 0.1 > ball.y))  && abs( ball.x-x ) < 0.2)
			{
				ball.yspeed = -ball.yspeed;
				alive = false;
			}

			if(((x - 0.3 < ball.x && x - 0.2 > ball.x) || (x + 0.3 > ball.x && x + 0.2 < ball.x))  && abs(ball.y-y) < 0.05)
			{
				ball.xspeed = -ball.xspeed;
				alive = false;
			}

		}
	}

	Tile(float a,float b, GLuint texture)
	{
		x=a;
		y=b;
		alive = true;
		logo = texture;

		endings = loadBMP_custom("endings.bmp");
		GLfloat buffer_data_for_logo[] = { 
		-2, -1, 0.0f,
		2, -1,0.0f,
		 2,  1, 0.0f,
		 -2, -1, 0.0f,
		-2, 1, 0.0f,
		 2,  1, 0.0f,

		 -2, -1, 0.0f,
		2, -1,0.0f,
		2, -1,1.0f,
		-2, 1,0.0f,
		2, 1,0.0f,
		2, 1,1.0f,

		-2, -1, 0.0f,
		-2, -1,1.0f,
		2, -1,1.0f,
		-2, 1, 0.0f,
		-2, 1,1.0f,
		2, 1,1.0f,

		-2, -1, 1.0f,
		2, -1,1.0f,
		 2,  1, 1.0f,
		 -2, -1,1.0f,
		-2, 1, 1.0f,
		 2,  1, 1.0f,

		2, -1, 1.0f,
		2, -1, 0.0f,
		2,  1, 0.0f,
		2, -1, 1.0f,
		2,  1, 1.0f,
		2,  1, 0.0f,

		-2, -1, 1.0f,
		-2, -1, 0.0f,
		-2,  1, 0.0f,
		-2, -1, 1.0f,
		-2,  1, 1.0f,
		-2,  1, 0.0f,
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



};

#endif