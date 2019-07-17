
#include "thing.h"

thing::thing(float w, float h, const char* path):

	t(path){

	ut = true;
	if(path == "") ut = false;
	unsigned int drawMode = GL_STATIC_DRAW;
	if(w == 0 && h == 0) drawMode = GL_DYNAMIC_DRAW;
	count = 1;
	offsetY = 0;

	vertices[0] = 0;
	vertices[1] = h;
	vertices[2] = 0;
	vertices[3] = 0.0f;
	vertices[4] = 0.0f;

	vertices[5] = w;
	vertices[6] = h;
	vertices[7] = 0;
	vertices[8] = 1.0f;
	vertices[9] = 0.0f;

	vertices[10] = w;
	vertices[11] = 0;
	vertices[12] = 0;
	vertices[13] = 1.0f;
	vertices[14] = 1.0f;

	vertices[15] = 0;
	vertices[16] = 0;
	vertices[17] = 0;
	vertices[18] = 0.0f;
	vertices[19] = 1.0f;

	glGenVertexArrays(1, &va);
	glGenBuffers(1, &vb);
	glGenBuffers(1, &eb);

	glBindVertexArray(va);
	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, drawMode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void thing::instance(unsigned int count_, glm::vec2 d[]){

	count = count_;

	if(count != 0){
	
		glBindVertexArray(va);

		unsigned int vb2;
		glGenBuffers(1, &vb2);

		glBindBuffer(GL_ARRAY_BUFFER, vb2);
	
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(glm::vec2), &d[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glVertexAttribDivisor(2, 1);
		glBindVertexArray(0);
	}	
}

void thing::setOffsetAndSize(float x, float y, float w, float h){

	vertices[0] = x;
	vertices[1] = y+h;

	vertices[5] = x+w;
	vertices[6] = y+h;

	vertices[10] = x+w;
	vertices[11] = y;

	vertices[15] = x;
	vertices[16] = y;

	glBindVertexArray(va);

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void thing::flip(){

	vertices[3] = 0.0f;
	vertices[4] = 1.0f;

	vertices[8] = 1.0f;
	vertices[9] = 1.0f;

	vertices[13] = 1.0f;
	vertices[14] = 0.0f;

	vertices[18] = 0.0f;
	vertices[19] = 0.0f;

	glBindVertexArray(va);

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void thing::display(){

	if(ut) t.bind();
	glBindVertexArray(va);
	if(count > 1) glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count);
	else if(count > 0) glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
