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
        void setMat3(const std::string &name, glm::mat3 value) const;
        void setMat2(const std::string &name, glm::mat2 value) const;
        void setVec3(const std::string &name, glm::vec3 &value) const;
        void setVec4(const std::string &name, glm::vec4 &value) const;
        void setVec2(const std::string &name, glm::vec2 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec2(const std::string &name, float x, float y) const;
};
#endif
