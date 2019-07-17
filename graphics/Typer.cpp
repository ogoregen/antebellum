
#include "Typer.h"

Typer::Typer():

	thing(0, 0){

	FT_Library ft;
	if(FT_Init_FreeType(&ft)) std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	FT_Face face;
	if(FT_New_Face(ft, "resources/fonts/consola.ttf", 0, &face)) std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for(GLubyte c = 0; c < 128; c++){ //register character set

		FT_Load_Char(face, c, FT_LOAD_RENDER);
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		Character character = {

			texture,
			glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		characters.insert(std::pair<GLchar, Character>(c, character));
	}

	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	thing.flip();
}

void Typer::scale(float s){

	scaleFactor = s;
}

void Typer::type(std::string input, float x, float y){

	std::string::const_iterator c;
	for(c = input.begin(); c != input.end(); c++){

		Character current = characters[*c];

		float x_ = x + current.bearing.x * scaleFactor;
		float y_ = y - current.bearing.y * scaleFactor;
		float w = current.size.x * scaleFactor;
		float h = current.size.y * scaleFactor;

		thing.setOffsetAndSize(x_, y_, w, h);
		x += (current.advance >> 6) * scaleFactor;

		glBindTexture(GL_TEXTURE_2D, current.textureID);
		thing.display();
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
