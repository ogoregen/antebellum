
#include "building.h"

int dimensiontable[5][2] = {

	1, 1,
	1, 2,
	2, 2,
	2, 3,
	3, 3
};

building::building(float x, float y, int type_):

	type(type_),
	dimensions(dimensiontable[type][0], dimensiontable[type][1]){
	
	glm::vec2 p(x, y);
	p *= 50;
	position = p;
}
