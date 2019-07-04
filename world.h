
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

		float worldsize;
		int tilecount = 7;
		int tilewidth = 100;
		int tileheight = tilewidth / 2;
		texture textures[7] = { //in order of drawing

			texture("resources/textures/sea.png"),
			texture("resources/textures/sea2.png"),
			texture("resources/textures/sea3.png"),
			texture("resources/textures/ground.png"),
			texture("resources/textures/low.png"),
			texture("resources/textures/low2.png"),
			texture("resources/textures/low3.png")
		};
		thing things[7] = {

			thing(tilewidth, textures[0].h / (textures[0].w / tilewidth)),
			thing(tilewidth, textures[1].h / (textures[1].w / tilewidth)),
			thing(tilewidth, textures[2].h / (textures[2].w / tilewidth)),
			thing(tilewidth, textures[3].h / (textures[3].w / tilewidth)),
			thing(tilewidth, textures[4].h / (textures[4].w / tilewidth)),
			thing(tilewidth, textures[5].h / (textures[5].w / tilewidth)),
			thing(tilewidth, textures[6].h / (textures[6].w / tilewidth)),
		};

	public:
		
		float seed;
		int **grid, **next;
		world(int worldsize, float seed_);
		void generate();
		void display();
};
