#include "world.h"

world::world(int worldsize_, float seed_) :

	seed(seed_),
	worldsize(worldsize_){

	for(int i = 0; i < tilecount; i++){

		things[0].offsetY = tileheight - textures[0].h / (textures[0].w / tilewidth);
	}
}

void world::generate(){

	grid = new int* [worldsize]; //create map data array
	for(int i = 0; i < worldsize; ++i) grid[i] = new int[worldsize];

	double xoff = 0.0;
	double yoff = 0.0;
	for(int i = 0; i < worldsize; i++){ //generate map

		yoff = 0.0;
		for(int j = 0; j < worldsize; j++){

			grid[i][j] = (int)map(stb_perlin_noise3(xoff, yoff, seed, 0, 0, 0), 0, 1, 0, 4);
			yoff += 0.01;
		}
		xoff += 0.01;
	}

	next = new int* [worldsize]; //create map data array
	for(int i = 0; i < worldsize; ++i) next[i] = new int[worldsize];

	for(int i = 0; i < worldsize; i++){ 

		for(int j = 0; j < worldsize; j++){

			if(grid[i][j] == 0){

				next[i][j] = (int)map(rand(), 0, RAND_MAX, 0, 3);
			}
			else{
			
				next[i][j] = (int)map(rand(), 0, RAND_MAX, 3, 6);
			} 
		}
	}

	grid = next;


	unsigned int* counts = new unsigned int[tilecount];
	for(int i = 0; i < tilecount; i++) counts[i] = 0;

	for(int i = 0; i < worldsize; i++){ //count each tile type 

		for(int j = 0; j < worldsize; j++){

			counts[grid[i][j]]++;
		}
	}

	glm::vec2** data = new glm::vec2*[tilecount];
	for(int i = 0; i < tilecount; i++) data[i] = new glm::vec2[counts[i]];

	int* iteration = new int[tilecount];
	for(int i = 0; i < tilecount; i++) iteration[i] = 0;

	for(int i = 0; i < worldsize; i++){ //fill the data arrays

		for(int j = 0; j < worldsize; j++){

			int c;
			c = grid[i][j];

			if(c >= 0 && iteration[c] < counts[c]){

				data[c][iteration[c]] = glm::vec2(ctoi(glm::vec2(i * tileheight, j * tileheight)).x, ctoi(glm::vec2(i * tileheight, j * tileheight)).y + things[c].offsetY);
				iteration[c]++;
			}
		}
	}

	for(int i = 0; i < tilecount; i++) things[i].instance(counts[i], data[i]); //pass the data arrays to shader
}

void world::display(){

	for(int i = 0; i < tilecount; i++){

		textures[i].bind();
		things[i].display();
	}
}
