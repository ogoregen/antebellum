
#pragma once

#include <iostream>
#include <cstdlib>

#include "stb_perlin/stb_perlin.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphics/thing.h"
#include "graphics/texture.h"

#include "functions.h"

class world{

	private:
		float seed;
		texture lowtile, seatile;
		thing sea, low, high, higher;

	public:
		world(int worldsize, float seed_);
		void display();
};
