# Textures

To add texture to the drawn figure

## Texture Wrapping

Texture coordinates usually range from (0,0) to (1,1). If not, there are other types too

![These are the examples](https://learnopengl.com/img/getting-started/texture_wrapping.png)



### glTexParameter*

takes three arguments
- texture target (2D or 3D)
-  what option we want to set and for which texture axis(S and/or T)
- texture wrapping mode

Note: if GL_CLAMP_TO_BORDER is used, border colour has to be specified too.This can be done by glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor)

## Texture Filtering

To figure out which texture pixel (or _texel_) to map the texture coordinate to. 

**Options** 
- GL_NEAREST (closest texel is chosen)
- GL_LINEAR (takes an interpolated value)

### Example:
![](https://learnopengl.com/img/getting-started/texture_filtering.png)

We can specify if we want to magnify or minify the image in use:- 

glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER(or GL_TEXTURE_MAG_FILTER) , GL_NEAREST(or LINEAR))

### Mipmaps

Creates several quality textures of a single texture to be used corresponding to the required object to be applied on to avoid waste of memory and other stuff.

glGenerateMipmaps will do the job for you.
Types:- 
- GL_NEAREST_MIPMAP_NEAREST
- GL_LINEAR_MIPMAP_NEAREST
- GL_NEAREST_MIPMAP_LINEAR
- GL_LINEAR_MIPMAP_LINEAR

Note: don't use this feature along with magnification

Can be later set by glTexParameteri.

## Loading And Creating Textures

### Popular header file
```
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

_stbi_load_ function is used to load an image to as a character pointer. 
- location
- width
- height
- no. of color channels

### Generating a texture

works just like a VBO or an VAO.

functions- glGenTextures, glBindTexture

#### glTexImage2D

Function inputs:-
- texture target
- mipmap level
- format of storage = GL_RGB
- width
- height
-  0 (always)
-  format (GL_RGB) and
- data type of source image
- actual image data

( call to generate mipmap if needed)

_stbi_image_free(data)_ to free memory

## Applying Textures

Add the texture coordinates to the vertices array adn pass it as you would for gradients.

Add another vertex attrib pointer for it too.

make changes in the vertex and fragment shader file

Built in data type called sampler  takes as  a postfix the texture type we want.

Both color and texture can be used together.

## Texture Units

We can use more than 1 texture objects at once.

GL_TEXTUREn (where n ranges from 0 to 15) can be used.

glActiveTexture is used to activate the texture no.

Then bind by glBindTexture

In shader frag, Fragcolor = mix( texture( texture1, TexCoord ) , texture( texture2, TexCoord ), 0.2 )

_stbi_set_flip_vertically_on_load(true)_ helps to load flipped vertically.
