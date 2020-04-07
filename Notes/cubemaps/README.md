# Cubemaps

- contains 6 individual 2D textures forming the sides of a textured cube.
- can be indexed/sampled using a direction vector.
- magnitude of this vector doesn't matter. Trick is OpenGL returns the texel value that the vector hits eventually.

## Creating a CubeMap

We initialize it like any other texture, this time binding it to _GL_TEXTURE_CUBE_MAP_.  Also, we need to bind each face to the glTexImage2D six different times.  These texture target enums are linearly stored and can be incremented to achieve our goal.

### texture_faces

Contains the locations of all the textures rewuired for cubemap (in order) . Pass the following parameters as before.

GL_CLAMP_TO_EDGE is used to adjust to limitations of hardware (as texture coordinates exactly between two faces might not hit an exact face).

Within the frag shader, we add a cubemap samplercube and a vec3 vector for direction instead of vec2.

## Displaying A Skybox

Large cube that gives the feeling of an environment. Hence, new vao, vbo and fresh set of vertices needed for it. 

As the cube is centred at origin we can use the position vector as texture coordinate too. We would also need new shaders too.

To centre the skybox around the pllayer, we remove the translation part of the matrix, so skybox wont come closer. This be done by taking the 3x3 matrix part from view matrix. and then recaling it to 4x4 matrix.


