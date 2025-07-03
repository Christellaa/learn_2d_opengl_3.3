#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include "includes.hpp"

class Shader {
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use();
		void setUniformInt(const std::string& uniformName, int value);
	private:
		unsigned int _programId;

		std::string retrieveGLSLCode(const char* path);
		unsigned int createShader(const std::string& type, const char* shaderCode);
		unsigned int createShaderProgram(unsigned int vertex, unsigned int fragment);
};

#endif
