
#pragma once

#include <iostream>
#include <cstdlib>
#include "stb_perlin/stb_perlin.h"
#include "graphics/texture.h"
#include "thing.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class world{

	private:
		texture low, sea;
		thing ss, ll;

	public:
		world(double seed);
		void display();
		glm::vec2 ctoi(glm::vec2 p);
		glm::vec2 itoc(glm::vec2 p);
};