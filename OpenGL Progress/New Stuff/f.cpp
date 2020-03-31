

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/readfile.hpp"
#include "utility/shader.hpp"
#include "Textures/texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Crisp As F", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glewExperimental = GL_TRUE;
    glewInit();
    
    GLfloat vertices[] =
    {
        -0.2f, 0.6f,  0.0f, 1.0, 0.0, 1.0,  0.4f, 0.8f,
        -0.2f, 0.4f, 0.0f,  1.0, 0.0, 0.0,  0.4f, 0.7f,
        -0.2f,-0.5f, 0.0f,  0.0, 1.0, 1.0,  0.4f, 0.25f,
        0.0f, -0.5f, 0.0f,  1.0, 0.0, 1.0,  0.5f, 0.25f,//3
        0.0f, 0.0f , 0.0f,  0.0, 1.0, 0.0,  0.5f, 0.5f, //4
        0.4f, 0.0f, 0.0f,   0.0, 0.0, 1.0,  0.7f, 0.5f, //5
        0.4f, 0.2f, 0.0f,   0.0, 1.0, 1.0,  0.7f, 0.6f,//6
        0.0f, 0.2f, 0.0f,   1.0, 0.0, 0.0,  0.5f, 0.6f, //7
        0.0f, 0.4f, 0.0f,   0.0, 0.0, 1.0,  0.5f, 0.7f, //8
        0.6f, 0.4f, 0.0f,   0.0, 1.0, 0.0,  0.8f, 0.7f,//9
        0.6f,0.6f,0.0f,     1.0, 1.0, 0.0,  0.8f, 0.8f 

    };
    GLuint indices[] =
    {
        0, 1, 10,
        10, 9, 1,
        1, 2, 3,
        1, 3, 8,
        4, 5, 6,
        6, 4, 7,
    };
    
    Shader *shdr = new Shader("shaders/shad.vs","shaders/shad.fs");
    Texture *txt = new Texture("Images/F.jpg");
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers( 1, &VBO );
    
    
    glBindVertexArray( VAO );
    
    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (3* sizeof(float)) );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (6* sizeof(float)) );
    glEnableVertexAttribArray(2);
    glBindBuffer( GL_ARRAY_BUFFER, 1);
    
    glGenBuffers( 1, &EBO);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray( 0 );
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        txt->use();
        shdr->use();
        glBindVertexArray( VAO );
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

