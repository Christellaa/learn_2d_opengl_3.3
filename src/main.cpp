#include "../include/includes.hpp"

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

void renderFrame(GLFWwindow* window)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void frameLoop(GLFWwindow* window)
{
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		renderFrame(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void createVBO()
{
	float vertices[] = {
    -0.5f, -0.5f, 0.0f, // bas gauche
     0.5f, -0.5f, 0.0f, // bas droite
     0.0f,  0.5f, 0.0f  // sommet
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void createShaderProgram()
{
	unsigned int vertexShader = createShader("vertex");
	unsigned int fragmentShader = createShader("fragment");
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// verif le linking
}

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
	"out vec4 fragColor;\n"
	"void main()\n"
	"{\n"
	"	fragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

unsigned int createShader(const std::string& type)
{
	const char** shaderSourceRef = nullptr;
	GLenum shaderType;
	if (type == "vertex")
	{
		shaderSourceRef = &vertexShaderSource;
		shaderType = GL_VERTEX_SHADER;
	}
	else if (type == "fragment")
	{
		shaderType = GL_FRAGMENT_SHADER;
		shaderSourceRef = &fragmentShaderSource;
	}

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSourceRef, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "Error: " << type << " shader compilation failed\n" << infoLog << std::endl;
	}
	return shader;
}

int main()
{
	initGLFW();
	GLFWwindow* window = initWindow();
	initGlad();
	glViewport(0, 0, 800, 600);
	createShaderProgram();
	// createVBO();
	frameLoop(window);
	glfwTerminate();
}
