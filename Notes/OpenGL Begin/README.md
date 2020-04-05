# Triangle (Single Program)

## Notes (My understanding)

### General methodology
 ![](https://learnopengl.com/img/getting-started/pipeline.png)
 
 Vertex data is input by float vertices array in 3d.
 
 ### VBO
 
 manages to store a lot of vertices into GPU memory.
 
 _glGENBuffers_(1, &VBO ) generates  buffer id (declare **VBO** first).
 
 several types of buffer objects. vertex type - **GL_ARRAY_BUFFER**.
 
 VBO is bound to it by glBindBuffer(GL_....., VBO).
 
 **GL_ARRAY_BUFFER** can now be used instead of VBO.
 
glBufferData function copies vertex data to the VBO object.  

### Vertex Shader

Create a source code for vertex shader

One of the shaders. Works on GLSL. Type name is GL_VERTEX_SHADER.

glCreateShader() assigns the type to the unsigned int hence defining a proper shader object

glShaderSource binds source code to the shader object. glCompileShaderto compile the object. *Option to check success in compilation can be performed*

### Fragment Shader

Input vec4 in source code (for RGB and Alpha)

GL_FRAGMENT_SHADER  is the type name.

Similarly bind and compile this like vertex shader.

### Shader Program

Links all the shaders. Create a program object (by glCreateProgram func)

glAttachShader( shader program, shader obj) links it. glLinkProgram does the rest.

glUseProgram can now be used to access the program created. Also, delete shader objects by glDeleteShader after linking with program.

### Linking Vertex Attributes

We define how the vertices fed work by glVertexAttribPointer() and then glEnableVertexAttribArray(). Might be a hectic task.

### VAO

Helps in storing calls to glEnableVertexAttribArray or disable the same.

Vertex attribute configurations via glVertexAttribPointer.

Vertex buffer objects associated with vertex attributes by calls to glVertexAttribPointer.

Called similar to VBO








 
 
 
