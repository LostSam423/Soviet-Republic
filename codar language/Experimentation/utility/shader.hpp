#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "readfile.hpp"
#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"
#include "glm/glm/gtc/type_ptr.hpp"
class Shader{
	GLuint ID;
	public:
		int success;
		char infoLog[512];
		Shader(const char* vertexPath, const char* fragmentPath);
		GLuint Shadertype(GLenum eShaderType, const char *filePath);
		void use();
        GLuint returnID();
        void setBool(const std::string &name, bool value)const;
        void setInt(const std::string &name, int value)const;
        void setFloat(const std::string &name, float value) const;
        void setMat4(const std::string &name, glm::mat4 value) const;
};
#endif
