
#include "functions.h"

glm::vec2 ctoi(glm::vec2 p){

	glm::vec2 i = p;
	i.x -= i.y;
	i.y = (p.x + p.y) / 2;
	return i;
}

glm::vec2 itoc(glm::vec2 p){

	glm::vec2 i = p;
	i.x = (p.x + 2 * p.y) / 2;
	i.y = (2 * p.y - p.x) / 2;
	return i;
}

double map(double x, double r1, double r2, double a1, double a2){

	double p = (r2 - r1) / (x - r1);
	double y = ((a2 - a1) / p) + a1;

	return y;
}
