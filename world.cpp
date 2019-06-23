
#include "world.h"

world::world(double seed):
	low("resources/textures/low.png"),
	sea("resources/textures/high.png"),
	ss(100, 50),
	ll(100, 50)
{

	int grid[400][400];

	double xoff = 0.0;
	double yoff = 0.0;
	unsigned int s_count = 0;
	unsigned int l_count = 0;
	for(int i = 0; i < 400; i++){

		yoff = 0.0;
		for(int j = 0; j < 400; j++){

			grid[i][j] = abs((int)(stb_perlin_noise3(xoff, yoff, seed, 0, 0, 0) * 4));

			if(grid[i][j] == 1){

				s_count++;
			}
			else l_count++;

			yoff += 0.005;
		}
		xoff += 0.005;
	}

	glm::vec2* ds = new glm::vec2[s_count];
	glm::vec2* dl = new glm::vec2[l_count];

	int a_ = 0;
	int b_ = 0;

	for(int i = 0; i < 400; i++){

		for(int j = 0; j < 400; j++){
		
			if(grid[i][j] == 1){
				if(a_ < s_count){

					ds[a_] = ctoi(glm::vec2(i * 50, j * 50));
					a_++;
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

	ss.init(s_count, ds);
	ll.init(l_count, dl);
}

void world::display(){

	low.bind();
	ll.display();
	sea.bind();
	ss.display();
}

glm::vec2 world::ctoi(glm::vec2 p){

	glm::vec2 i = p;
	i.x -= i.y;
	i.y = (p.x + p.y) / 2;
	return i;
}

glm::vec2 world::itoc(glm::vec2 p){

	glm::vec2 i = p;
	i.x = (p.x + 2 * p.y) / 2;
	i.y = (2 * p.y - p.x) / 2;
	return i;
}
