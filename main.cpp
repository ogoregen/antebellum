
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image/stb_image.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "graphics/shader.h"
#include "graphics/texture.h"

#include "thing.h"

int irr1, irr2, width, height;
double mouseX, mouseY;
glm::vec2 translation(0, 0);
GLFWwindow* window;

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

static void view(){

	glfwGetCursorPos(window, &mouseX, &mouseY);
	if(mouseX < 15) translation.x += 15;
	else if(mouseX > width - 15) translation.x -= 15;
	if(mouseY < 15) translation.y += 15;
	else if(mouseY > height - 15) translation.y -= 15;

	glClear(GL_COLOR_BUFFER_BIT);
}

static void hud(){

	ImGui_ImplGlfwGL3_NewFrame();
	{
		ImGui::Text("average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(window);
	glfwPollEvents();
}

static int initialize(){

	if(!glfwInit()) return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwGetMonitorWorkarea(glfwGetPrimaryMonitor(), &irr1, &irr2, &width, &height);
	window = glfwCreateWindow(width, height, "lite", glfwGetPrimaryMonitor(), NULL);
	if(!window){

		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	if(glewInit() != GLEW_OK) return -1;
	std::cout << "Be positive, please. " << "Using " << glGetString(GL_VERSION) << std::endl;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

int main(void){
	
	glm::vec2 d[1600];

	int a = 0;
	for(int i = 0; i < 40; i++){

		for(int j = 0; j < 40; j++){

			d[a] = ctoi(glm::vec2(i*50, j*50));
			a++;
		}
	}

	initialize();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

	shader basic("resources/shaders/basic_vs.shader", "resources/shaders/basic_fs.shader");
	texture texturea("resources/textures/low.png");
	texture textureb("resources/textures/high.png");
	thing ad(200, 100, 1600, d);
	thing ad2(400, 200, 1);

	basic.bind();

	while(!glfwWindowShouldClose(window)){

		view();

		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));

		basic.setUmat4f("mvp", proj * view);

		texturea.bind();
		ad.display();

		hud();
	}

	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
