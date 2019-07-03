
#include "button.h"

button::button(float x, float y) :

	buttontexture("resources/textures/button.png"),
	pressedtexture("resources/textures/button2.png"),
	buttonthing(50, 50)
{

	position = glm::vec2(x, y);
}

bool button::hovering(double mouseX, double mouseY){

	if(mouseX < position.x + 50 && mouseX > position.x &&
		 mouseY < position.y + 100 && mouseY > position.y) return true;;
	return false;
}

void button::display(double mouseX, double mouseY){

	if(hovering(mouseX, mouseY)) pressedtexture.bind();
	else buttontexture.bind();
	buttonthing.display();
}
