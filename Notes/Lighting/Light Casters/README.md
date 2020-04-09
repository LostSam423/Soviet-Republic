# Light Casters

Generally, not all light types come from a source, as seen till now. There are several types of **Light Casters**.
- Directional light
- Point light
- Spotlights

## Directional Light

When the light rays are parallel to each other. which implies light source is at infinity, hence independent of its location.

As the light direction is constant, we can directly use the vector by negating and normalizing it. (hence making it point towards the light source).

We have to pass a uniform light direction vector too.
As it is just a direction vectore, we should pass it as vec3. If we do define it as a vec4, we need to set w to 0.

## Point Lights
Generally, the light siurce in a point light system has a limited intensity and fades with distance. But in previous examples, no such implementation is observed.
We can achieve this by attenuation.

### Attenuation

Formula for attenuation:-
![Attenuation Formula](https://i.ibb.co/C7FLZ1v/Screenshot-2020-04-09-at-7-23-58-AM.png)

Here d represents the distance from the fragment to the light source. Then to calculate the attenuation value we define 3 (configurable) terms: a constant term **Kc**, a linear term **Kl** and a quadratic term **Kq**. 

The constant term is usually kept at 1.0 .

### Implementation
Add the constant uniforms to Light struct. And apply the formula. Also update the final values.

## Spotlight  (Nice movie)

Acts like a conical spectrum of light. Represnted by 
- World space position
- direction
- cutoff angle

In opengl, the following terms are needed to be taken care of

    LightDir: the vector pointing from the fragment to the light source.
    SpotDir: the direction the spotlight is aiming at.
    Phi ϕ: the cutoff angle that specifies the spotlight's radius. Everything outside this angle is not lit by the spotlight.
    Theta θ: the angle between the LightDir vector and the SpotDir vector. The θ value should be smaller than Φ to be inside the spotlight.

### Flashlight
We pass position and front of camera as position and direction, and cosinde of an angle as the cutoff angle.
We calculate theta in the frag shader, and compare it with cutoff and apply accordingly.k

### Smooth Em Edges

To achive smoothness, we can define another outer cone. Then we would apply a factor of intensity to the places outside the inner but inside the outer cone.
![formula](https://i.ibb.co/pJ3sTnw/Screenshot-2020-04-09-at-8-41-11-AM.png)
Here ϵ (epsilon) is the cosine difference between the inner (ϕ) and the outer cone (γ) (ϵ=ϕ−γ). The resulting I value is then the intensity of the spotlight at the current fragment. 
![valueees](https://i.ibb.co/DzbGLjG/Screenshot-2020-04-09-at-8-45-59-AM.png)

We can get rid of the if else now, by using a clamp.
 Make sure you add the outerCutOff value to the Light struct and set its uniform value in the application
