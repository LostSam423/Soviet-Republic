#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"

	Texture::Texture(const char *Filename )
	{
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   // set texture wrapping to GL_REPEAT (default wrapping method)
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    	stbi_set_flip_vertically_on_load(true);

    	unsigned char *data = stbi_load(Filename, &width, &height, &nrChannels, 0);
    	if (data)
   	 	{	
        	
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        	glGenerateMipmap(GL_TEXTURE_2D);
    	}
    	else
    	{
        	std::cout << "Failed to load texture" << std::endl;
    	}
    
    	stbi_image_free(data);
	}

	void Texture::use(int i)
	{
		glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, texture);	
	}