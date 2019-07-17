
#pragma once
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H  
#include <iostream>
#include "shader.h"
#include "thing.h"

class Typer{

	private:

		thing thing;
		float scaleFactor = 1;
		struct Character{

			unsigned int textureID; //ID handle of the glyph texture
			glm::vec2 size; // size of glyph
			glm::vec2 bearing; // offset from baseline to left/top of glyph
			int advance; //offset to advance to next glyph
		};
		std::map<GLchar, Character> characters;

	public:
		Typer();
		void scale(float s);
		void type(std::string input, float x, float y);
};