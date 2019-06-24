
#include "world.h"

world::world(int worldsize, float seed_):

	lowtile("resources/textures/low.png"),
	seatile("resources/textures/sea.png"),
	sea(100, 50),
	low(100, 50),
	high(100, 50),
	higher(100, 50),
	seed(seed_)
{

	sea.offset = 5;
	high.offset = -10;
	higher.offset = -5;

	unsigned int s_count = 0;
	unsigned int l_count = 0;
	unsigned int h_count = 0;
	unsigned int h2_count = 0;

	int** grid = new int* [worldsize];
	for(int i = 0; i < worldsize; ++i) grid[i] = new int[worldsize];

	double xoff = 0.0;
	double yoff = 0.0;
	for(int i = 0; i < worldsize; i++){

		yoff = 0.0;
		for(int j = 0; j < worldsize; j++){

			grid[i][j] = (int) map(stb_perlin_noise3(xoff, yoff, seed, 0, 0, 0), 0, 1, 2, 5);
			if(grid[i][j] == 1) s_count++;
			else if(grid[i][j] == 4) h2_count++;
			else if(grid[i][j] == 3) h_count++;
			else l_count++;
			yoff += 0.02;
		}
		xoff += 0.02;
	}

	glm::vec2* ds = new glm::vec2[s_count];
	glm::vec2* dl = new glm::vec2[l_count];
	glm::vec2* dh = new glm::vec2[h_count];
	glm::vec2* dh2 = new glm::vec2[h2_count];

	int a_ = 0;
	int b_ = 0;
	int c_ = 0;
	int d_ = 0;

	for(int i = 0; i < worldsize; i++){

		for(int j = 0; j < worldsize; j++){
		
			if(grid[i][j] == 1){
				if(a_ < s_count){

					ds[a_] = glm::vec2(ctoi(glm::vec2(i * 50, j * 50)).x, ctoi(glm::vec2(i * 50, j * 50)).y + sea.offset);
					a_++;
				}
			}
			else if(grid[i][j] == 3){
				if(c_ < h_count){

					dh[c_] = glm::vec2(ctoi(glm::vec2(i * 50, j * 50)).x, ctoi(glm::vec2(i * 50, j * 50)).y + high.offset);
					c_++;
				}
			}
			else if(grid[i][j] == 4){
				if(d_ < h2_count){

					dh2[d_] = glm::vec2(ctoi(glm::vec2(i * 50, j * 50)).x, ctoi(glm::vec2(i * 50, j * 50)).y + higher.offset);
					d_++;
				}
			}
			else{
				if(b_ < l_count){

					dl[b_] = ctoi(glm::vec2(i * 50, j * 50));
					b_++;
				}
			}
		}
	}

	sea.init(s_count, ds);
	low.init(l_count, dl);
	high.init(h_count, dh);
	higher.init(h2_count, dh2);
}

void world::display(){

	seatile.bind();
	sea.display();

	lowtile.bind();
	low.display();
	high.display();
	higher.display();
}
