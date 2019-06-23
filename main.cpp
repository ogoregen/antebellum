
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
#include <imgui\imgui_impl_glfw_gl3.h>

#include "graphics/shader.h"
#include "graphics/texture.h"

#include "thing.h"
#include "world.h"

int irr1, irr2, width, height;
double mouseX, mouseY;
glm::vec2 translation(0, 0);
GLFWwindow* window;
float zoom = 0.1;

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
		ImGui::SliderFloat("scale", &zoom, 0.1f, 1.0f);
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
	

	initialize();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

	shader basic("resources/shaders/basic_vs.shader", "resources/shaders/basic_fs.shader");
	world map(10);

	basic.bind();

	while(!glfwWindowShouldClose(window)){

		view();

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(zoom, zoom, zoom));
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));

		basic.setUmat4f("mvp", proj * view * scale);

		map.display();

		hud();
	}

	glfwTerminate();
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	return 0;
}
