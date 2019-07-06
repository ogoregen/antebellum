
#include <iostream>
#include <vector>
#include <time.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include <imgui/imgui_impl_glfw_gl3.h>
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/thing.h"
#include "interface/button.h"
#include "world.h"
#include "buildings.h"

int irr1, irr2, displaywidth, displayheight, width, height;
double mouseX, mouseY;
glm::vec2 translation(0, 0);
glm::vec2 cursor;
GLFWwindow* window;
float zoom = 1;
bool add = false;
int selector_ = 0;

void mousepressed(GLFWwindow* window, int button, int action, int mods){

	if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){

		add = true;
	}
}

void onscroll(GLFWwindow* window, double xoffset, double yoffset){

	if(yoffset > 0 && zoom < 1){

		zoom += 0.1;
		translation.y += height / 2 - mouseY;
		translation.x += width / 2 - mouseX;
	}
	else if(yoffset < 0 && zoom >= 0.7){

		zoom -= 0.1;
	}
}

void view(){

	glfwGetCursorPos(window, &mouseX, &mouseY);
	if(mouseX < 15.0f) translation.x += 15.0f;
	else if(mouseX > width - (double)15.0f) translation.x -= 15.0f;
	if(mouseY < 15.0f && translation.y < 0) translation.y += 15.0f;
	else if(mouseY > height - (double)15.0f) translation.y -= 15.0f;
}

void hud(){

	ImGui_ImplGlfwGL3_NewFrame();
	{	
		ImGui::Text("average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SliderInt("building selector", &selector_, 0, 4);
	}
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

int initialize(){

	if(!glfwInit()) return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &irr1, &irr2, &displaywidth, &displayheight);
	width = displaywidth;
	height = displayheight;
	window = glfwCreateWindow(width, height, "lite", NULL, NULL);
	if(!window){

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if(glewInit() != GLEW_OK) return -1;
	std::cout << "Be positive, please. " << std::endl << "Using " << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetScrollCallback(window, onscroll);
	glfwSetMouseButtonCallback(window, mousepressed);
}

int main(void){

	initialize();
	buildings b;
	shader basic("resources/shaders/basic_vs.shader", "resources/shaders/basic_fs.shader");
	basic.bind();
	glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
	srand(time(NULL));
	world map(200, (int)rand());
	std::cout << "Seed: " << map.seed << std::endl;
	map.generate();

	texture selectortile("resources/textures/selector.png");
	thing selector(selectortile.w/2, selectortile.h/2);
	selector.offsetY = -7.5;

	button buttons[1] = {

		button(40, height - 80)
	};

	while(!glfwWindowShouldClose(window)){

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
		glClear(GL_COLOR_BUFFER_BIT);

		cursor = glm::vec2(mouseX - translation.x, mouseY - translation.y);
		cursor = itoc(cursor);
		cursor.x = int(cursor.x / 50);
		cursor.y = int(cursor.y / 50);
		//cursor.x -= 1;
		cursor.y += 1;
		cursor = ctoi(cursor);
		cursor *= 50;

		view();

		if(add){

			b.add(cursor.x / 50, cursor.y / 50, selector_);
			add = false;
		}

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, zoom));
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));

		basic.setUmat4f("mvp", proj * view * scale);
		map.display();

		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(cursor.x, cursor.y + selector.offsetY, 0));
		basic.setUmat4f("mvp", proj * view * scale * model);
		selectortile.bind();
		selector.display();

		basic.setUmat4f("mvp", proj * view * scale);
		b.display(); //display the buildings

		for(int i = 0; i < std::size(buttons); i++){

			glm::mat4 model2 = glm::translate(glm::mat4(1.0f), glm::vec3(buttons[i].position.x, buttons[i].position.y, 0));
			basic.setUmat4f("mvp", proj * model2);
			buttons[i].display(mouseX, mouseY);
		}

		hud();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	return 0;
}
