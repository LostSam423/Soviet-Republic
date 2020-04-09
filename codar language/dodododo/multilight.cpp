

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/readfile.hpp"
#include "utility/shader.hpp"
#include "Textures/texture.hpp"
#include "utility/camera.hpp"

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


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool firstMouse = true;
float lastX =SCR_WIDTH/2.0f;
float lastY = SCR_HEIGHT/2.0f;


glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

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
    
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };

    GLfloat skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
    };

    glEnable(GL_DEPTH_TEST);

    Shader *skyboxshdr = new Shader("shaders/shadsky.vs", "shaders/shadsky.fs");
    
    GLuint skyboxVBO, skyboxVAO;
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);

    glBindVertexArray( skyboxVAO );

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (GLvoid * ) 0);
    glEnableVertexAttribArray(0);

     std::string arr[] = {
    "Images/skybox/right.jpg",
    "Images/skybox/left.jpg",
    "Images/skybox/top.jpg",
    "Images/skybox/bottom.jpg",
    "Images/skybox/front.jpg",
    "Images/skybox/back.jpg"
    };
    std::vector<std::string> faces(arr, arr + sizeof(arr)/ sizeof(std::string));
    unsigned int cubemapTexture = loadCubemap(faces);   

    skyboxshdr->use();
    skyboxshdr->setInt("skybox", 0);

    Shader *lightingshdr = new Shader("shaders/lightmaps.vs","shaders/multilight.fs");
    Shader *lightsrcshdr = new Shader("shaders/lightsrc.vs", "shaders/lightsrc.fs");
    Texture *txt = new Texture("Images/box1.jpg");
    Texture *txt1 = new Texture("Images/specbox1.jpg");
    GLuint VBO, contVAO;
    glGenVertexArrays(1, &contVAO);
    glGenBuffers( 1, &VBO );

    glBindVertexArray( contVAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (3* sizeof( GLfloat )));
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (6* sizeof( GLfloat )));
    glEnableVertexAttribArray( 2 );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

    GLuint lightsrcVAO;
    glGenVertexArrays(1, &lightsrcVAO);

    glBindVertexArray( lightsrcVAO );

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    
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
        
        lightingshdr->use();
        lightingshdr->setInt("material.diffuse",0);
        lightingshdr->setInt("material.specular",1);
        lightingshdr->setFloat("material.shininess", 32.0f);
        lightingshdr->setVec3("viewPos", camera.Position);
        txt->use(0);
        txt1->use(1);

        lightingshdr->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        lightingshdr->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        lightingshdr->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        lightingshdr->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        lightingshdr->setVec3("pointLights[0].position", pointLightPositions[0]);
        lightingshdr->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        lightingshdr->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        lightingshdr->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        lightingshdr->setFloat("pointLights[0].constant", 1.0f);
        lightingshdr->setFloat("pointLights[0].linear", 0.09);
        lightingshdr->setFloat("pointLights[0].quadratic", 0.032);
        // point light 2
        lightingshdr->setVec3("pointLights[1].position", pointLightPositions[1]);
        lightingshdr->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        lightingshdr->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        lightingshdr->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        lightingshdr->setFloat("pointLights[1].constant", 1.0f);
        lightingshdr->setFloat("pointLights[1].linear", 0.09);
        lightingshdr->setFloat("pointLights[1].quadratic", 0.032);
        // point light 3
        lightingshdr->setVec3("pointLights[2].position", pointLightPositions[2]);
        lightingshdr->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        lightingshdr->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        lightingshdr->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        lightingshdr->setFloat("pointLights[2].constant", 1.0f);
        lightingshdr->setFloat("pointLights[2].linear", 0.09);
        lightingshdr->setFloat("pointLights[2].quadratic", 0.032);
        // point light 4
        lightingshdr->setVec3("pointLights[3].position", pointLightPositions[3]);
        lightingshdr->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        lightingshdr->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        lightingshdr->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        lightingshdr->setFloat("pointLights[3].constant", 1.0f);
        lightingshdr->setFloat("pointLights[3].linear", 0.09);
        lightingshdr->setFloat("pointLights[3].quadratic", 0.032);
        // spotLight
        lightingshdr->setVec3("spotLight.position", camera.Position);
        lightingshdr->setVec3("spotLight.direction", camera.Front);
        lightingshdr->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        lightingshdr->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        lightingshdr->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        lightingshdr->setFloat("spotLight.constant", 1.0f);
        lightingshdr->setFloat("spotLight.linear", 0.09);
        lightingshdr->setFloat("spotLight.quadratic", 0.032);
        lightingshdr->setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
        lightingshdr->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
        
        
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.0f);
        lightingshdr->setMat4("projection",projection);
        
        glm::mat4 view = glm::mat4(1.0f);
        view = camera.GetViewMatrix();
        lightingshdr->setMat4("view",view);

        glBindVertexArray(contVAO);
        for(unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            lightingshdr->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        lightsrcshdr->use();
        lightsrcshdr->setMat4("view", view);
        lightsrcshdr->setMat4("projection",projection);
        
        glBindVertexArray(lightsrcVAO);
        for (unsigned int i = 0; i < 4; i++)
         {
             glm::mat4 model = glm::mat4(1.0f);
             model = glm::translate(model, pointLightPositions[i]);
             model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
             lightsrcshdr->setMat4("model", model);
             glDrawArrays(GL_TRIANGLES, 0, 36);
         }

         // draw skybox as last
        glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
        skyboxshdr->use();
        view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
        skyboxshdr->setMat4("view", view);
        skyboxshdr->setMat4("projection", projection);
        // skybox cube
        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
        glDepthFunc(GL_LESS);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays( 1, &contVAO );
    glDeleteVertexArrays(1, &lightsrcVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &skyboxVBO);
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
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

unsigned int loadCubemap(std::vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
} 