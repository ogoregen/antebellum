
#pragma once
#include "glm/glm.hpp"
#include "functions.h"

class building{

	private:
		
		int type;

	public:

		glm::vec2 position, dimensions;
		building(float x, float y, int type_);
};