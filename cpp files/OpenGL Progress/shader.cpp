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
