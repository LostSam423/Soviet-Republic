#include "shader.hpp"


	Shader::Shader(const char *vertexPath, const char *fragmentPath){
		int success;
		char infoLog[512];
		
		GLuint vshad = Shadertype(GL_VERTEX_SHADER, vertexPath);
		GLuint fshad = Shadertype(GL_FRAGMENT_SHADER, fragmentPath);

		ID = glCreateProgram();
		glAttachShader(ID, vshad);
		glAttachShader(ID, fshad);
		glLinkProgram(ID);

		 glGetProgramiv(ID, GL_LINK_STATUS, &success);

    	if (!success){
        	glGetProgramInfoLog(ID, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    	}

    	glDeleteShader(vshad);
    	glDeleteShader(fshad);

	}
	GLuint Shader::Shadertype(GLenum eShaderType, const char *filePath)
	{	
		int success;
		char infoLog[512];
		std::string shader = getFile(filePath);
		const char *Shadertext = shader.c_str();
		GLuint shad;
		shad = glCreateShader(eShaderType);
		glShaderSource(shad, 1, &Shadertext, NULL);
		glCompileShader(shad);

		glGetShaderiv(shad, GL_COMPILE_STATUS, &success);
		if(!success){
			glGetShaderInfoLog(shad, 512, NULL, infoLog);
        	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    	}
    	return shad;

	}
	void Shader::use(){
		glUseProgram(ID);
	}

	GLuint Shader::returnID()
	{
		return ID;
	}

	void Shader::setBool(const std::string &name, bool value) const
    {         
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
    }
    // ------------------------------------------------------------------------
    void Shader::setInt(const std::string &name, int value) const
    { 
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
    }
    // ------------------------------------------------------------------------
    void Shader::setFloat(const std::string &name, float value) const
    { 
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
    }
    void Shader::setMat4(const std::string &name, glm::mat4 value) const
    {
    	glUniformMatrix4fv(glGetUniformLocation(ID,name.c_str()),1, GL_FALSE,glm::value_ptr(value));
    }
