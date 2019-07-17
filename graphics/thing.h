
#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "texture.h"

class thing{

	private:
		texture t;
		bool ut;
		unsigned int va, eb, count, vb;
		float vertices[20];
		unsigned int indices[6] = {0, 1, 3,	1, 2, 3};

	public:
		float offsetY;
		thing(float w, float h, const char* path = "");
		void instance(unsigned int count_, glm::vec2 d[] = 0);
		void setOffsetAndSize(float x, float y, float w, float h);
		void flip();
		void display();
};
