#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "readfile.hpp"

class Shader{
	GLuint ID;
	public:
		int success;
		char infoLog[512];
		Shader(const char* vertexPath, const char* fragmentPath);
		GLuint Shadertype(GLenum eShaderType, const char *filePath);
		void use();
};
#endif