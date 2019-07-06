
#include "buildings.h"

buildings::buildings():

	roadmanager(){

	things[0].offsetY = -44 - 7.5; //we need a way to pass this here from world.cpp
	things[1].offsetY = 50 - textures[1].h/2 - 7.5;
	things[2].offsetY = -88 - 7.5;
	things[3].offsetY = 75 - textures[3].h / 2 - 7.5;
	things[4].offsetY = 100 - textures[4].h/2 - 7.5;
}

void buildings::add(float x, float y, int type){

	list[type].push_back(building(x, y, type));
	update(type);
	//add roads here? yes.
	roadmanager.add(building(x, y, type));
}

void buildings::update(int type){
	
	if(!busy){ //this is probably totally unnecessary

		busy = true;
		counts[type] = list[type].size();
		int count = counts[type];
		glm::vec2* positions = new glm::vec2[count]; //data array to pass to the shader

		for(int i = 0; i < count; i++){ //filling the data array

			positions[i] = list[type][i].position;
			positions[i].y += things[type].offsetY;
		}

		//if one building has another behind it, draw the one on the front again later

		if(count > 0) things[type].instance(count, positions);
		busy = false;
	}
}

void buildings::display(){

	roadmanager.display();

	for(int i = 0; i < typecount; i++){

		textures[i].bind();
		if(counts[i] > 0) things[i].display();
	}
}
