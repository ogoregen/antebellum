
#include "roads.h"

roads::roads(){

	things[0].offsetY = -7.5;
	things[1].offsetY = -7.5;
	things[2].offsetY = -7.5;
	things[3].offsetY = -7.5;
	things[4].offsetY = -7.5;
	things[5].offsetY = -7.5;
}

void roads::update(){

	for(int i = 0; i < typecount; i++){

		counts[i] = positions[i].size();

		glm::vec2* data = new glm::vec2[counts[i]]; //data array to pass to the shader

		for(int a = 0; a < counts[i]; a++){ //filling the data array

			data[a] = positions[i][a];
		}

		if(counts[i] > 0) things[i].instance(counts[i], data);
	}
}

void roads::add(building b){

	for(int a = 0; a < b.dimensions.x; a++){
		for(int c = 0; c < b.dimensions.y; c++){

		for(int i = -1; i <= 1; i++){

			for(int j = -1; j <= 1; j++){

				glm::vec2 p(b.position.x, b.position.y);

				p = itoc(p);
				p /= 50;
				p.x += i;
				p.y += j;
				p.x += a;
				p.y -= c;
				p *= 50;
				p = ctoi(p);

				if(i != 0 || j != 0){

					if(a == 0 && i == -1){

						if(j == 0) positions[0].push_back(glm::vec2(p.x, p.y + things[0].offsetY));

					}
					if(a == b.dimensions.x - 1 && i == 1){

						if(j == 0) positions[0].push_back(glm::vec2(p.x, p.y + things[0].offsetY));
					}

					if(c == 0 && j == 1){

						if(i == 0) positions[1].push_back(glm::vec2(p.x, p.y + things[1].offsetY));
					}

					if(c == b.dimensions.y - 1 && j == -1){

						if(i == 0) positions[1].push_back(glm::vec2(p.x, p.y + things[1].offsetY));
					}

					if(a == 0 && c == 0){

						if(i == -1 && j == 1) positions[5].push_back(glm::vec2(p.x, p.y + things[5].offsetY));
					}
					if(a == b.dimensions.x - 1 && c == b.dimensions.y - 1){

						if(i == 1 && j == -1) positions[4].push_back(glm::vec2(p.x, p.y + things[4].offsetY));
					}
					if(a == b.dimensions.x - 1 && c == 0){ //S

						if(i == 1 && j == 1) positions[2].push_back(glm::vec2(p.x, p.y + things[2].offsetY));
					}
					if(a == 0 && c == b.dimensions.y - 1){

						if(i == -1 && j == -1) positions[3].push_back(glm::vec2(p.x, p.y + things[3].offsetY));
					}
				}
			}
		}
		}
	}
	update();
}

void roads::display(){

	for(int i = 0; i < typecount; i++){

		textures[i].bind();
		if(counts[i] > 0) things[i].display();
	}
}
