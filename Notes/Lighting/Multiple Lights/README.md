# Multiple Lights
To use multiple lights we can store our options as functions and then use them in the main as required.

Per implementation, actual code might differ, but the general structure would remain same.

## Directional Light
For this we create a struct DirLight, and define it as a uniform. 

This uniform can be passed easily into a function.

## Point Light

Here we define another struct PointLight with its own values.

Similarly we can use a function to use the point light system.
We can use a preproceesor directive to define the no. of elements in an array and then use the constant later.
## Spotlight

Do the same for spotlight
And voila, you have a multilight system
