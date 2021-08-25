#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include "Utils.hpp"


static uint32_t compileShader(uint32_t type, const std::string& source) {
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (!result) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		auto message = std::vector<char>(length);
		glGetShaderInfoLog(id, length, &length, &message[0]);

		std::cout << "Failed to compile " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader !" << std::endl;
		std::cout << message.data() << std::endl;


		glDeleteShader(id);
		return 0;
	}
	return id;

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

	uint32_t VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	uint32_t EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	std::string vertexShaderSrc = readShaderFile("shaders/VertexShader.glsl");
	std::string fragmentShaderSrc = readShaderFile("shaders/FragmentShader.glsl");
	uint32_t vertexShader;
	uint32_t fragmentShader;

	vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
	fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	uint32_t shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	glUseProgram(shaderProgram);


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

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