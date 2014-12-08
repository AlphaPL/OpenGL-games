#ifndef CUBE_HPP
#define CUBE_HPP

#include "Sphere.hpp"


class Cube: public Sphere
{
	public:
		Cube(char textureToLoad[], char vertexShader[], char fragmentShader[]): Sphere(textureToLoad, vertexShader, fragmentShader)
		{ }




};

#endif