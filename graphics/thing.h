
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class thing{

	private:
		unsigned int va, eb, count;
		float vertices[20];
		unsigned int indices[6] = {0, 1, 3,	1, 2, 3};

	public:
		float offset;
		thing();
		thing(float w, float h);
		thing(float w, float h, unsigned int count_, glm::vec2 d[]);
		void init(unsigned int count_, glm::vec2 d[] = 0);
		void display();
};

