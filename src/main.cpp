#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"


int main() {
	glfwInit();
	GLFWwindow* window = glfwCreateWindow(1080, 720, "Learn OpenGL", nullptr, nullptr);

	if(!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	const int result = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	if(!result) {
		std::cout << "Could not load GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	});

	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 2   // first triangle
	};

	VertexArray vertexArray;
	vertexArray.bind();



	Shader shader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

	auto vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	vertexBuffer->setLayout({
		{ShaderDataType::Float3, "aPos"},
		{ShaderDataType::Float3, "aColor"}
	});

	vertexArray.addVertexBuffer(std::move(vertexBuffer));
	vertexArray.setIndexBuffer(std::make_unique<IndexBuffer>(indices, sizeof(indices)));



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		glDrawElements(GL_TRIANGLES, vertexArray.getIndexBuffer().getCount(), GL_UNSIGNED_INT, nullptr);

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}