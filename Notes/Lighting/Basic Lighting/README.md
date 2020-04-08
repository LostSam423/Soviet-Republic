# Basic Lighting

Lighting in OpenGL is performed by **Phong lighting model**. 
It consists of three components:-
- Ambient Lighting
- Diffuse Lighting
- Specular Lighting

## Ambient Lighting

We add a small factor to the object so that even when it is completely dark, there is this constant that gives the object some color.

## Diffuse Lighting

This finds how much light ray affects by its positioning relative to the object(s). This can be found by normal vector's angle with the light ray. 

Steps:
- add normal to the vertices
- import it to frag shader
- Find the frag position in real world by model matrix
- find light direction vector and normalize
- take dot and multiply it to result (remember to take the max of dot and 0 in case dot is less than 0)

Use of normal matrix - used so that the normal we found isn't affected by non uniform scale factor.
 This is done by transpose of inverse.

## Specular Lighting
SImilar to diffuse lighting, it also takes into account the view direction of observer. In short, reflective property of surface.

This takes into consideration the position of viewer, here, the camera.
specular strength is defined to adjust the brightness.
Use math to find out the reflectDirection and other vectors necessary.
