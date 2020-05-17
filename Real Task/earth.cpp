#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/readfile.hpp"
#include "utility/shader.hpp"
#include "Textures/texture.hpp"
#include "utility/camera.hpp"
#include "utility/skybox.hpp"
#include "objects/cube.hpp"
#include "objects/sphere.hpp"

#include "utility/glm/glm/glm.hpp"
#include "utility/glm/glm/gtc/matrix_transform.hpp"
#include "utility/glm/glm/gtc/type_ptr.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadCubemap(std::vector<std::string> faces);
// settings
float deltaTime= 0.0f;
float lastframe=0.0f;
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
bool blinn = false;
bool blinnKeyPressed = false;

bool pointlight = true;
bool directional = false;
bool spotlight = false;
bool pointlightKeyPressed = true;
bool directionalKeyPressed = false;
bool spotlightKeyPressed = false;

Camera camera(glm::vec3(0.0f, 0.0f, 30.0f));
bool firstMouse = true;
float lastX =SCR_WIDTH/2.0f;
float lastY = SCR_HEIGHT/2.0f;

glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
glm::vec3 lightDirection(1.0f, 0.0f, 0.0f);
int lightType = 1;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glewExperimental = GL_TRUE;
    glewInit();
    
    
    
    glEnable(GL_DEPTH_TEST);

    Shader *skyboxshdr = new Shader("shaders/shadsky.vs", "shaders/shadsky.fs");
    
    std::string arr[] = {
    "Images/skybox/star.jpg",
    "Images/skybox/star.jpg",
    "Images/skybox/star.jpg",
    "Images/skybox/star.jpg",
    "Images/skybox/star.jpg",
    "Images/skybox/star.jpg"
    };

    std::vector<std::string> faces(arr, arr + sizeof(arr)/ sizeof(std::string));
    
    Skybox skybox(faces);  

    skyboxshdr->use();
    skyboxshdr->setInt("skybox", 0);

    Shader *lightingshdr = new Shader("shaders/earth.vs","shaders/earth.fs");
    Texture *txt = new Texture("Images/night.jpg");
    Texture *txt1 = new Texture("Images/earth.jpg");
    Texture *txt2 = new Texture("Images/earthspec.jpg");

    Sphere earth(10.0f, 120);                                                        
    
    while (!glfwWindowShouldClose(window))
    {
        
        float currentframe = glfwGetTime();
        deltaTime=currentframe-lastframe;
        lastframe=currentframe;
        // input
        // -----
        processInput(window);
         
        // render
        // ------

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);

        
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();


        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[0]);
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3(1.0f, 0.3f, 0.5f));

        
        lightingshdr->use();
        glm::mat4 normalMat = glm::transpose(glm::inverse(model));

        lightingshdr->setMat4("normalMatrix",normalMat);
        lightingshdr->setVec3("viewLoc", camera.Position);
        lightingshdr->setMat4("projection",projection);
        lightingshdr->setMat4("view",view);
        lightingshdr->setMat4("model", model);

        lightingshdr->setVec3("light.position", lightPos);
        lightingshdr->setVec3("light.direction", lightDirection);
        lightingshdr->setInt("light.type", lightType);
        lightingshdr->setInt("light.constant", 1.0f);
        lightingshdr->setFloat("light.linear", 0.04f);
        lightingshdr->setFloat("light.quadratic", 0.0003f);
        

        lightingshdr->setVec3("light.ambient", 1.0f, 1.0f, 1.0f);
        lightingshdr->setVec3("light.diffuse", 0.8f,0.8f,0.8f);
        lightingshdr->setVec3("light.specular", 0.5f, 0.5f, 0.5f);

        lightingshdr->setInt("material.ambient",0);
        lightingshdr->setInt("material.diffuse",1);
        lightingshdr->setInt("material.specular",2);
        lightingshdr->setFloat("material.shininess", 30.0f);
        
        txt->use(0);
        txt1->use(1);
        txt2->use(2);
        glBindVertexArray(earth.VAO);
        glDrawArrays(GL_TRIANGLES, 0, earth.vertex_count);
        
         // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxshdr->use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxshdr->setMat4("view", view);
        skyboxshdr->setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skybox.skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, earth.vertex_count);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays( 1, &earth.VAO );
    glDeleteVertexArrays(1, &skybox.skyboxVAO);
    glDeleteBuffers(1, &skybox.skyboxVBO);
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = deltaTime*5.0f; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS && !blinnKeyPressed)
    {
        blinn = !blinn;
        blinnKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_RELEASE)
        blinnKeyPressed = false;

    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && !pointlightKeyPressed)
    {
        pointlight = !pointlight;
        pointlightKeyPressed = true;
        directionalKeyPressed = false;
        spotlightKeyPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_RELEASE)
        pointlightKeyPressed = false;

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS && !directionalKeyPressed)
    {
        directional = !directional;
        pointlightKeyPressed = false;
        directionalKeyPressed = true;
        spotlightKeyPressed = false;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_RELEASE)
        directionalKeyPressed = false;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS && !spotlightKeyPressed)
    {
        spotlight = !spotlight;
        pointlightKeyPressed = false;
        directionalKeyPressed = false;
        spotlightKeyPressed = true;
    }
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_RELEASE)
        spotlightKeyPressed = false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina  displays.
    glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
  
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}  
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
