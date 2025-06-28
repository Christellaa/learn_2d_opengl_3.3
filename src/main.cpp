#include "../include/includes.hpp"
#include "../include/Shader.hpp"

void initGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLFWwindow* initWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "2dtest", NULL, NULL);
	if (window == NULL)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(1);
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	return window;
}

void initGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to init GLAD" << std::endl;
		glfwTerminate();
		exit(1);
	}
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void renderFrame(GLFWwindow* window, Shader& shaderProgram, unsigned int VAO)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shaderProgram.use();
	glBindVertexArray(VAO);
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void frameLoop(GLFWwindow* window, Shader& shaderProgram, unsigned int VAO)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		renderFrame(window, shaderProgram, VAO);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

unsigned int createVAO()
{
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	return VAO;
}

unsigned int createVBO()
{
	float vertices[] = {
	// pos x, y, z
    -0.5f, -0.5f, 0.0f, // bas gauche -> sommet 0
     0.5f, -0.5f, 0.0f, // bas droite -> sommet 1
     0.5f,  0.5f, 0.0f,  // haut droite -> sommet 2
    -0.5f,  0.5f, 0.0f  // haut gauche -> sommet 3
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	return VBO;
}

unsigned int createEBO()
{
	unsigned int indexes[] = {
		2, 1, 3, // first triangle
		1, 0, 3 // second triangle
	};

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
	return EBO;
}

int main()
{
	initGLFW();
	GLFWwindow* window = initWindow();
	initGlad();
	glViewport(0, 0, 800, 600);
	unsigned int VAO = createVAO();
	unsigned int VBO = createVBO();
	unsigned int EBO = createEBO();
	Shader shaderProgram("../shaders/vertex.vs", "../shaders/fragment.fs");
	glBindVertexArray(0);
	frameLoop(window, shaderProgram, VAO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
