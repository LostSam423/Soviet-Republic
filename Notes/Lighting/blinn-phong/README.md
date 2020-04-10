# Advanced Lighting

## Blinn-Phong Lighting method

Phong has disadvantages, has specular reflection breakdown in certain conditions.
For example in the image below, the light beyond the edges is immediately cut off.

We define a new halfway vector instead of reflection vector as the unit vector, exactly halfway  between view direction and light direction.
 When the view direction is perfectly aligned with the (now imaginary) reflection vector, the halfway vector aligns perfectly with the normal vector. The closer the view direction is to the original reflection direction, the stronger the specular highlight.
 
 In blinn-phong we wont have the issue of cutoff anymore.
 We can add a switch that would switch between phong and blinn phong model by choice.

## Normal Mapping

Generally a surface is not completely flat, and has rough edges.
But we generally use a plane texture to cover up. We can deal with it by adding a normal map, which basically defines a proper depth to the surface, and uses normal component per fragment and not per surface.    
Load the corresponfing textures to fragment shaders.

One issue is that the normal vectors we used were all pointing in the z direction. This wouldnt be the case if the normal vector would be pointing to y direction. 

Hence we introduce a new coordinate space that transforms all the z pointing normal vectors accordingly

## Tangent Space

Normal vectors here are expressed in a tangent space, where they point in positive z direction.
Then we use a matrix to transform all the normal vectors into their respective coordinates.
This matrix is called **TBN** matrix 1e. Tangent, Bitangent and Normal vector. _Change of basis_ is what we will be doing basically. Hence, we would need perpendicular coordinate system to do so.

This can be simply done by using linear algebra. and we have a orthogonal system.

Two ways to go about the implementation of TBN matrix.
- Pass the TBN matrix to fragment shader and transform the sampled normal from tangent space to world space.
- Take inverse of matrix to transform from world space to tangent space and transform all vectors except the normal

Catch with the first method, although it may seem easy, is that each time fragment shader runs, it has to calculate the matrix multiplication. But if we try second approach, we can calculate the necessary inverse in the vertex shader itself and pass the inverse, hence optimising the solution.
