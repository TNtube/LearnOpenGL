#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <iostream>
#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"
#include "Renderer/Texture.hpp"


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
		// positions          // colors           // texture coords
		100.0f, 100.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		200.0f, 100.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		200.0f, 200.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		100.0f, 200.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		2, 3, 0    // second triangle
	};

	VertexArray vertexArray;
	vertexArray.bind();

	auto vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	vertexBuffer->setLayout({
		{ShaderDataType::Float3, "aPos"},
		{ShaderDataType::Float3, "aColor"},
		{ShaderDataType::Float2, "aTexPos"}
	});

	vertexArray.addVertexBuffer(std::move(vertexBuffer));
	vertexArray.setIndexBuffer(std::make_unique<IndexBuffer>(indices, sizeof(indices)));

	Shader shader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

	Texture texture("assets/container.jpg");





	while (!glfwWindowShouldClose(window))
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		auto MVP = glm::ortho(0.0f, (float)w, 0.0f, (float)h, -1.0f, 1.0f);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		shader.setUniformMat4("u_MVP", MVP);
		vertexArray.bind();
		texture.bind();
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