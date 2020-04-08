# Materials
In general, objects of different material have different reaction to light. 

We hence can define a struct comprising of all the Phong properties and also the shininess( for the spilling of reflected light).

## Setting materials
We update the fragment shader by adding the material struct and changing the uniforms into a singular Material uniform. But we have to set the objects in the main program individually.
```
struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
```
## Light Properties
The problem in previous section is its brightness (which is too much). We can solve this by introducing a factor in each of the phong components.

One effective way out would be intriducing another struct of light which stores all the factors needed to be multiplied to the components.
```
struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
```
Update the necessary changes.

## Different Light Colors

Now that we have access to the colors through the main program, we can play with the colors and add more options with sin and glfwGetTime().
