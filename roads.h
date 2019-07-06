
#pragma once
#include "building.h"
#include "thing.h"
#include "texture.h"
#include <vector>
#include "functions.h"

class roads{

	private:
		
		int typecount = 6;
		std::vector<glm::vec2>* positions = new std::vector<glm::vec2>[6];
		texture textures[6] = {

			texture("resources/textures/road.png"),
			texture("resources/textures/roadL.png"),
			texture("resources/textures/roadS.png"),
			texture("resources/textures/roadN.png"),
			texture("resources/textures/roadE.png"),
			texture("resources/textures/roadW.png")
		};
		thing things[6] = { //needs to be automated like in world.cpp

			thing(100, textures[0].h / 2),
			thing(100, textures[1].h / 2),
			thing(100, textures[2].h / 2),
			thing(100, textures[3].h / 2),
			thing(100, textures[4].h / 2),
			thing(100, textures[5].h / 2)
		};
		int counts[6];
		void update();

	public:

		roads();
		void add(building b);
		void display();
};
