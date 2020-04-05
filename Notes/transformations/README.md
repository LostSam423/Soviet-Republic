# Transformations

We do this by using multiple matrix objects. As frame by frame change would be quite hectic.

## Pre-learnings
- Vectors
- Scalars
- Matrices and its operations

## Matrix-Vector Multiplication Theory

Generally we work with 4x4 matrices

### Identity Matrix

No change in the vector

### Scaling

We multiply a matrix with first three 1s as diff numbers, as is the necessary scale factor for each coordinate, and keep the fourth 1 as it is for translation, later. 

### Translation

Here, the fourth column of matrix is replaced by translation coordinates along with the 1. This results in translation of each coordinate by required distance.

### Homogeneous Coordinate

The w coordinate is also called homogeneous coordinate. Helps in translation. We need to divide x, y, z by w to get the 3D vector. If w=0, then vector is direction vector (cant be translated).

### Rotation

Rotation matrices can be multipolied in various forms for rotation along respective axes.

![rotation forms](https://i.ibb.co/3ywFFkY/Screenshot-2020-04-04-at-2-01-19-AM.png)

If we use an order to rotate first by x, y and z, then we face a _gimbal lock_ situation. Hence we use the following matrix, where (Rx, Ry, Rz) is an arbitrary unit vector.

![](https://i.ibb.co/5RrhdxR/Screenshot-2020-04-04-at-2-09-01-AM.png)

### Combining Matrices

Easily done by multiplying the required matrices.

As matrix multiplication is not commutative, the order is important.

## Working

Header only library used = GLM (0r Open**GL** **M**athematics)

commands used generally:

- glm::vec4 = for vector initialization
- glm::mat4 = for matrix initialization
- glm::translate(matrix, vector)
- glm::scale(matrix, vector)
- glm::rotate(matrix, glm::radians(90.0f), axis of rotation)
- glm::value_ptr(matrix)

Pass the resulting matrix as a uniform value by 
```
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```
We can now multiply the uniform to the position vec in vertex shader.

For time dependent rotations and translations, we need to define the uniform in render loop

## Additional Info from Lec Slides

### 2D Transformations

#### Shear 
[1 c]

[0 1]
