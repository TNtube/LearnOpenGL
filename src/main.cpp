#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer/VertexArray.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"


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
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 2,   // first triangle
		2, 3, 0    // second triangle
	};

	VertexArray vertexArray;
	vertexArray.bind();

	Shader shader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

	auto vertexBuffer = std::make_unique<VertexBuffer>(vertices, sizeof(vertices));
	vertexBuffer->setLayout({
		{ShaderDataType::Float3, "aPos"},
		{ShaderDataType::Float3, "aColor"},
		{ShaderDataType::Float2, "aTexPos"}
	});

	vertexArray.addVertexBuffer(std::move(vertexBuffer));
	vertexArray.setIndexBuffer(std::make_unique<IndexBuffer>(indices, sizeof(indices)));

	uint32_t texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);



	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		glBindTexture(GL_TEXTURE_2D, texture);
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