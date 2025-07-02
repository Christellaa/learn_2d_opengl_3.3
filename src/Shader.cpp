#include "../include/Shader.hpp"

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	std::string vertexCode = retrieveGLSLCode(vertexPath);
	std::string fragmentCode = retrieveGLSLCode(fragmentPath);
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	unsigned int vertex = createShader("vertex", vertexShaderSource);
	unsigned int fragment = createShader("fragment", fragmentShaderSource);

	this->_programId = createShaderProgram(vertex, fragment);
}

Shader::~Shader()
{
	glDeleteProgram(this->_programId);
	glfwTerminate();
}

std::string Shader::retrieveGLSLCode(const char* path)
{
	std::string code;
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file.open(path);
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		code = ss.str();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: Shader file could not be successfully read\n" << e.what() << std::endl;
	}
	return code;
}

unsigned int Shader::createShader(const std::string& type, const char* shaderCode)
{
	GLenum shaderType;
	if (type == "vertex")
		shaderType = GL_VERTEX_SHADER;
	else if (type == "fragment")
		shaderType = GL_FRAGMENT_SHADER;

	unsigned int shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
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

unsigned int Shader::createShaderProgram(unsigned int vertex, unsigned int fragment)
{
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertex);
	glAttachShader(shaderProgram, fragment);
	glLinkProgram(shaderProgram);

	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "Error: shader program compilation failed\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return shaderProgram;
}


void Shader::use() {
	glUseProgram(this->_programId);
}
