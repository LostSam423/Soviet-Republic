# Coordinate Systems

![](https://learnopengl.com/img/getting-started/coordinate_systems.png)

 - Local coordinates are the coordinates of your object relative to its local origin; they're the coordinates your object begins in.
- The next step is to transform the local coordinates to world-space coordinates which are coordinates in respect of a larger world. These coordinates are relative to some global origin of the world, together with many other objects also placed relative to this world's origin.
- Next we transform the world coordinates to view-space coordinates in such a way that each coordinate is as seen from the camera or viewer's point of view.
- After the coordinates are in view space we want to project them to clip coordinates. Clip coordinates are processed to the -1.0 and 1.0 range and determine which vertices will end up on the screen. Projection to clip-space coordinates can add perspective if using perspective projection.
- And lastly we transform the clip coordinates to screen coordinates in a process we call viewport transform that transforms the coordinates from -1.0 and 1.0 to the coordinate range defined by _glViewport_. The resulting coordinates are then sent to the rasterizer to turn them into fragments.

## Projection 

### Local Space
The coordinate space where we first start drawing. with generally the start point being (0,0,0).
Hence all vertices of objects created are in local space. hence, local.

### World Space
How we import an object form local space defines the world space.
This is by multiplying **model** matrix to local space object vertices. This is how you want your objects to be positioned.

### View Space
Usually referred to as camera of opengl. Transforming your world space coordinates to coordinates that are in camera's view. Mostly comprises of translation/ rotations. **View** matrix is used to get this transformation.

### Clip Space
All coordinates are to be in a certain range and anything that falls outside must be clipped.
Coordinates clipped are discarded. 

Projetcion Matrix is used to perform the transformation. It specifies a range of coordinates from -1000 to 1000 in ech dimension. Then this is converted to -1.0, 1.0 ie. Normalized Device Coordinates (or NDC). 
```
Note: If only a part of a primitive e.g. a triangle is outside the clipping volume OpenGL will reconstruct the triangle as one or more triangles to fit inside the clipping range. 
```
### Perspective division
A final operation where we divide the x, y, z by the homogenous w component. This step is performed automatically at the end of vertex shader step.

Next, the viewport transform does the job to map it into screen coordinates.

## Projection Matrix Types

### Orthographic
Defines a cube like frustum box with clipping space, where each vertex outside this box is clipped. We specify width, height and length of the frustum. 
`````
glm::ortho(left end, right end, bottom , top, near, far)
`````
The coordinates are directly transformed.

### Perspective
The further away a given vertex, smaller it should appear. Thus it is handled by the homogenous coordinate, by dividing the x, y, z by w.
```
glm::mat4 proj = glm::perspective(field of view(angle), aspect ratio(generally viewport's width/height, near, far )
```
## Into 3D-verse

1. Make a model matrix, angle it accordingly ( by rotate ).
2. Next, create a view matrix. 
Note: To move a camera backwards, is the same as moving the entire scene forward.
3. Create a projection matrix.
4. Pass all as uniform and multiply in order to vertex position.

## More 3D
1. Define a lot of vertices, this time also using z coordinate to make a cube.
2. You can add glfwGetTime to rotate the model.

### Z-buffer
OpenGL stores depth knowledge of each fragment as the z-value. When you enable GL_DEPTH_TEST, it compares the depth value at each fragment and chooses the above one.

We can now create a lot of objects and push them to different coordinates for more view.
