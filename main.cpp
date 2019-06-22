
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

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();
}

float vertices[] = { //x, y, z, s, t

	 0.0f,   50.0f, 0.0f, 1.0f, 1.0f,
	 100.0f, 50.0f, 0.0f, 1.0f, 0.0f,
   100.0f, 0.0f,  0.0f, 0.0f, 0.0f,
	 0.0f,   0.0f,  0.0f, 0.0f, 1.0f
};

unsigned int indices[] = {

	0, 1, 3,
	1, 2 ,3
};

glm::vec2 d[10000];

int main(void){

	int a = 0;
	for(int i = 0; i < 100; i++){

		for(int j = 0; j < 100; j++){

			d[a] = ctoi(glm::vec2(i*70, j*70));
			a++;
		}
	}

	initialize();
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 proj = glm::ortho(0.0f, (float)width, (float)height, 0.0f);

	shader basic("resources/shaders/basic_vs.shader", "resources/shaders/basic_fs.shader");

	int w, h, channelcount;
	unsigned char* image = stbi_load("resources/textures/low.png", &w, &h, &channelcount, 0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, 0);

	stbi_image_free(image);

	unsigned int va, vb, vb2, eb;

	glGenVertexArrays(1, &va);
	glGenBuffers(1, &vb);
	glGenBuffers(1, &vb2);
	glGenBuffers(1, &eb);

	glBindVertexArray(va);
		glBindBuffer(GL_ARRAY_BUFFER, vb);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eb);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)( 3 *sizeof(float)));
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vb2);
		glBufferData(GL_ARRAY_BUFFER, 10000 * sizeof(glm::vec2), &d[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
		glVertexAttribDivisor(2, 1);
	glBindVertexArray(0);

	while(!glfwWindowShouldClose(window)){

		glfwGetCursorPos(window, &mouseX, &mouseY);
		if(mouseX < 15) translation.x += 15;
		else if(mouseX > w - 15) translation.x -= 15;
		if(mouseY < 15) translation.y += 15;
		else if(mouseY > h - 15) translation.y -= 15;
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(translation.x, translation.y, 0));

		glClear(GL_COLOR_BUFFER_BIT);

		basic.bind();

		basic.setUmat4f("mvp", proj * view);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(va);
		glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, 10000);


		ImGui_ImplGlfwGL3_NewFrame();

		{
			ImGui::Text("average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}
