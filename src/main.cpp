#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include "Renderer/Buffer.hpp"
#include "Renderer/Shader.hpp"


static GLenum ShaderDataTypeToOpenGLType(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3:
		case ShaderDataType::Float4:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4:
			return GL_FLOAT;
		case ShaderDataType::Int:
		case ShaderDataType::Int2:
		case ShaderDataType::Int3:
		case ShaderDataType::Int4:
			return GL_INT;
		case ShaderDataType::Bool:
			return GL_BOOL;
		default:
			std::cout << "Unknown ShaderDataType." << std::endl;
			assert(false);
			return 0;
	}
}


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

	uint32_t VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer vertexBuffer(vertices, sizeof(vertices));
	vertexBuffer.bind();

	IndexBuffer indexBuffer(indices, sizeof(indices));
	indexBuffer.bind();

	Shader shader("shaders/VertexShader.glsl", "shaders/FragmentShader.glsl");

	vertexBuffer.setLayout({
		{ShaderDataType::Float3, "aPos"},
		{ShaderDataType::Float3, "aColor"}
	});

	vertexBuffer.bind();

	uint32_t index = 0;
	auto layout = vertexBuffer.getLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
				      element.getElementCount(),
				      ShaderDataTypeToOpenGLType(element.type),
				      element.normalized ? GL_TRUE : GL_FALSE,
				      layout.getStride(),
				      reinterpret_cast<const void*>(element.offset));
		index++;
	}


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}