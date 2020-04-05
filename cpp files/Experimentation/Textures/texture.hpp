#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "stb_image.h"

class Texture{
	GLuint texture;
	int ID;
	public:
		int width, height, nrChannels;
		Texture( const char *Filename);

		void use(int i=0);

};
#endif
