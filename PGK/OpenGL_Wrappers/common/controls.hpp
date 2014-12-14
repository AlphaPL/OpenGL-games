#ifndef CONTROLS_HPP
#define CONTROLS_HPP
void computeMatricesFromInputs(vec3& monkeyPos);

class Control
{
	public:
		static mat4 ViewMatrix;
		static mat4 ProjectionMatrix;
		static bool inGame;
		static void computeMatricesFromInputs(vec3& monkeyPos);
		static glm::mat4 getViewMatrix();
		static glm::mat4 getProjectionMatrix();
};

#endif