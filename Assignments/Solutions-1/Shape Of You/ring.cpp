

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/shader.hpp"
#include "utility/readfile.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void chessmatrix(float *vertices);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const int size = 8*8*3*3*2;

int main()
{   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Soviet Republic", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    float *vertices=new float [size];
    chessmatrix(vertices);
    glViewport(0, 0,SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader *shdr = new Shader("shaders/shad1.vs","shaders/shad1.fs");    
     GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers( 1, &VBO );
    for (int i = 0; i < size; ++i)
    {
        std::cout<<vertices[i]<<std::endl;
    }
    
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO);
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );

    glVertexAttribPointer( 1, 1, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), (GLvoid * ) (2* sizeof( GLfloat )) );
    glEnableVertexAttribArray( 1 );
    
    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glfwPollEvents();

        glClearColor(0.8f, 0.6f, 0.7f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shdr->use();

        glBindVertexArray( VAO );

        glDrawArrays(GL_TRIANGLES, 0, size/3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays( 1, &VAO );
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void chessmatrix(float *vertices)
{
    vertices = new float[size];
    float incr = 0.2f;
    float check = -1.0f;
    int index=0;
    for (int i = -4; i < 4; ++i)
    {
        for (int j = -4; j < 4; ++j)
        {   
            float leftbotx = (float)i*incr; float leftboty = (float)j*incr; 
            float lefttopx= leftbotx; float lefttopy = leftboty+incr;
            float rightbotx = leftbotx + incr;  float rightboty = leftboty;
            float righttopx= leftbotx + incr;  float righttopy = leftboty+ incr;
            
            vertices[index] = leftbotx; index++; 
            vertices[index] = leftboty; index++; 
            vertices[index] = check; index++;
            vertices[index] = rightbotx; index++; 
            vertices[index] = rightboty; index++; 
            vertices[index] = check;index++;
            vertices[index] = lefttopx; index++; 
            vertices[index] = lefttopy; index++; 
            vertices[index] = check;index++;
            vertices[index] = rightbotx; index++; 
            vertices[index] = rightboty; index++; 
            vertices[index] = check;index++;
            vertices[index] = lefttopx; index++; 
            vertices[index] = lefttopy; index++; 
            vertices[index] = check;index++;
            vertices[index] = righttopx; index++; 
            vertices[index] = righttopy; index++; 
            vertices[index] = check; index++;
            check*=(-1);   
        }
    }
    std::cout<<index;
    
}


