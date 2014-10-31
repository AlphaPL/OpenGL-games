#ifndef BACK_HPP
#define BACK_HPP

class Background
{

public:

	GLint data_buffer;
	GLint logo_buffer;
	GLint logo_border_buffer;
	GLuint uvbuffer;
	GLuint TableTex;
	GLuint logo;
	GLuint logo_back;

	void draw(mat4 MVP,mat4 Projection, mat4 View, mat4 Model, GLint TextureShaders , GLint MatrixID , GLint TextureID)
	{
		MVP = Projection * View * Model* glm::translate(mat4(1.0f),vec3(0,0,-75)) * glm::scale(glm::vec3(30.0f,30.0f,30.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);
		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), -90.0f, vec3(1,0,0)) * glm::translate(mat4(1.0f),vec3(0,0,-150)) * glm::scale(glm::vec3(60.0f,60.0f,60.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);
		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), 90.0f, vec3(1,0,0)) * glm::translate(mat4(1.0f),vec3(0,0,-150)) * glm::scale(glm::vec3(60.0f,60.0f,60.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);
		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), -90.0f, vec3(0,1,0)) * glm::translate(mat4(1.0f),vec3(0,0,-150)) * glm::scale(glm::vec3(60.0f,60.0f,60.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);
		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), 90.0f, vec3(0,1,0)) * glm::translate(mat4(1.0f),vec3(0,0,-150)) * glm::scale(glm::vec3(60.0f,60.0f,60.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);
		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), 180.0f, vec3(0,1,0)) * glm::translate(mat4(1.0f),vec3(0,0,-150)) * glm::scale(glm::vec3(60.0f,60.0f,60.0f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, data_buffer, uvbuffer, TableTex, TextureID,6);

		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), 180.0f, vec3(0,1,0)) * glm::translate(mat4(1.0f),vec3(0,0,-80))* glm::scale(glm::vec3(1.0f,0.5f,0.5f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, logo_buffer, uvbuffer, logo, TextureID,6);

		MVP = Projection * View * Model* glm::rotate(mat4(1.0f), 180.0f, vec3(0,1,0)) * glm::translate(mat4(1.0f),vec3(0,0,-81))* glm::scale(glm::vec3(1.0f,0.5f,0.5f));
		DrawWithTexture(TextureShaders, MatrixID, MVP, logo_buffer, uvbuffer, logo_back, TextureID, 18);

	}

	Background()
	{
		TableTex = loadBMP_custom("stars.bmp");
		logo = loadBMP_custom("arkanoid.bmp");
		logo_back = loadBMP_custom("arkanoid_back.bmp");
		GLfloat buffer_data_for_table[] = { 
		-5.5f, -4.1f, -1.5f,
		5.5f, -4.1f,-1.5f,
		 5.5f,  4.1f, -1.5f,
		 -5.5f, -4.1f, -1.5f,
		-5.5f, 4.1f, -1.5f,
		 5.5f,  4.1f, -1.5f,
		};

		GLfloat buffer_data_for_logo[] = { 
		-10.5f, -4.1f, -3.5f,
		10.5f, -4.1f,-3.5f,
		 10.5f,  4.1f, -3.5f,
		 -10.5f, -4.1f, -3.5f,
		-10.5f, 4.1f, -3.5f,
		 10.5f,  4.1f, -3.5f,

		 -10.5f, -4.1f, -3.5f,
		10.5f, -4.1f,-3.5f,
		10.5f, -4.1f,-1.5f,
		-10.5f, 4.1f, -3.5f,
		10.5f, 4.1f,-3.5f,
		10.5f, 4.1f,-1.5f,

		-10.5f, -4.1f, -3.5f,
		-10.5f, -4.1f,-1.5f,
		10.5f, -4.1f,-1.5f,
		-10.5f, 4.1f, -3.5f,
		-10.5f, 4.1f,-1.5f,
		10.5f, 4.1f,-1.5f,
		};


		data_buffer = genBuffer(buffer_data_for_table,sizeof(buffer_data_for_table));

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
			0, 1,
			1, 1,
		};

		uvbuffer  = genBuffer((GLfloat*)uv_data_for_table, sizeof(uv_data_for_table));
	}

};

#endif