# Camera
View matrix is generally involved. Hence, simulating a camera by moving all objects of scene in the reverse direction, [**illusion 100**].

## Camera/View Space

### Camera Position
Can be controlled by translating the camera.
```
glm::vec3 cameraPos = glm::vec3(coordinates);
```
Hence to move camera backwards, we need to move it in positive z axis

### Camera Direction
We get the direction of camera by subtraction its positon with origin. Mind that we consder the negation of the actual camera direction.
````
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
````
### Right Axis
Represents the positive x-axis of camera axis. We do this by first specifying an up vector and then cross product with direction vector.
```
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```
### Up Axis
This is found by cross product of camera direction and camera right.
```
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
```
## Look At
This defines a 3D space with perpendicular axes and translation vector. We can make our own look at matrix now that we have a perpendicular coordinate system and a position vector of camera.
![look at matrix](https://i.ibb.co/68H5ncy/Screenshot-2020-04-05-at-2-45-53-PM.png)

We can see that the rotation matrix is transposed and translation negated, since we move the camera in opposite direction of the required motion.
Hence it creates a view matrix.

Long story short, glm::lookAt does the task for us. We just need to input the position, target and up vector.

## Walk Around
Setting up a camera system.

Define some vectors and use lookat to form a matrix. _Set the target as camerapos + camerafront, so that the camera points at the target direction._

Now we fiddle with the processInput function.
```void processInput(GLFWwindow *window)
{
    ...
    const float cameraSpeed = 0.05f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
```
Here, glfwGetKey registers the key being pressed and acts upon it.
On front and back, we need to change camerapos value

### Movement Speed

For packing a standard constant cam speed, we define **deltatime** that keeps the speed constant according to the frame speed. Define global variables deltatime, lastframe and calc the frame time diff and use it accordingly.

## Look Around

Using mouse to look around.

### Euler Angles
![Euler chacha](https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png)
- Pitch :-  The angle that depicts bow much we are looking up or down. X axis
- Yaw :- The magnitude we are lookin left or right. Y axis.
- Roll :- How much we roll.

Each angle is represented by a single value and with their combination, we get rotation matrix.
Yaw and Pitch are used to determine the direction vector.
```
direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
direction.y = sin(glm::radians(pitch));
direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
```
yaw is determined at -90.0f to maintain positive z axis.

### Mouse Input
Horizontal mouse movement = yaw

Vertical = pitch

1. Hide the cursor and _capture_ it. Can ne done by 
````
glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
````
Like keyboard, we would need a mouse callback function that uses x and y positions of mouse. 
```
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
```
2. Calculate the mouse's offset since the last frame.
3. Add the offset values to the camera's yaw and pitch values.
4. Add some constraints to the minimum/maximum pitch values.
5. Calculate the direction vector.

### Zoooooooom
changes the field of view. We have a callback function for mouse scrolling too.
We alter the fov of projection matrix and connect it to the mouse scroll.

Create camera classs for it now. Wait, What? ;-)
