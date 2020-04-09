# Lighting Maps

Long story short, we are going to use textures for lighting. All parts of an object do not have the same shininess and do not reflect the same amount of light than others. Hence, we use _diffuse_ and _specular_ maps for such purpose (because ambient lighting would be same for all).

## Diffuse Maps
Basically adding a texture.

We store the texture data sampler2D in the struct Material in place of diffuse vec3. Also, no need of ambient vector anymore. Hence we replace material.diffuse with the general texture usage.

## Specular Maps

It provides proper specular highlight to each region of the object. We create a new texture and load it as specular material. All other loadings are similar as a general texture. Do update the frag shader accordingly.

