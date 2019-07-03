
#pragma once

#include "glm/glm.hpp"

#include "thing.h"
#include "texture.h"

class button{

	private:
		texture buttontexture, pressedtexture;
		thing buttonthing;

	public:
		glm::vec2 position;
		button(float x, float y);
		bool hovering(double mouseX, double mouseY);
		void display(double mouseX, double mouseY);
};
