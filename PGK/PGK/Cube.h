#ifndef CUBE_H
#define CUBE_H
#include "Sphere.hpp"

class Cube : public Sphere
{
public:
	Cube(char textureToLoad[], char vertexShader[], char fragmentShader[], vec3 dcolor): Sphere(textureToLoad, vertexShader, fragmentShader, dcolor)
	{
		ModelMatrix = glm::scale(glm::mat4(1.0f),vec3(100,10000,100000));
	}
};


#endif