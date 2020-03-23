# Triangle (SIngle Program)

## Notes (My understanding)

### General methodology
 ![](https://learnopengl.com/img/getting-started/pipeline.png)
 
 Vertex data is input by float vertices array in 3d.
 
 VBO manages to store a lot of vertices into GPU memory.
 
 _glGENBuffers_(1, &VBO ) generates  buffer id (declare **VBO** first).
 
 several types of buffer objects. vertex type - **GL_ARRAY_BUFFER**.
 
 VBO is bound to it by glBindBuffer(GL_....., VBO).
 
 **GL_ARRAY_BUFFER** can now be used instead of VBO.
 
glBufferData function copies vertex data to the VBO object.  
 
 
 
 
