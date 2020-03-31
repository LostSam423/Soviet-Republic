

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "utility/shader.hpp"
#include "utility/readfile.hpp"

#include "Textures/texture.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void drawRing(GLfloat *vertices, GLuint *indices, int N);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const int N = 360;

 
int main()
{   
    GLfloat vertices[N*8];
    GLuint indices[N*2];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "One Ring To Rule Them All", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    glewExperimental = GL_TRUE;
    glewInit();
    
    glViewport(0, 0,SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    drawRing(vertices, indices, N);
    Shader *shdr = new Shader("shaders/shad.vs","shaders/shad.fs");    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers( 1, &VBO );
    
    
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( vertices ), vertices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (3* sizeof(GLfloat)) );
    glEnableVertexAttribArray( 1 );

    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 8* sizeof( GLfloat ), (GLvoid * ) (6* sizeof(GLfloat)) );
    glEnableVertexAttribArray( 2 );

    glGenBuffers( 1, &EBO);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    Texture *txt = new Texture("Images/ring2.jpg");

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        txt->use();
        shdr->use();

        glBindVertexArray( VAO );

        glDrawElements(GL_LINES, N*2, GL_UNSIGNED_INT, 0);

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

void drawRing(GLfloat *vertices, GLuint *indices, int N)
{
    GLfloat centre = 0.0f;
    GLfloat rad = 0.5f;
    float i = 0;

    while(i<=N){
        GLfloat x = centre + rad * cos(i*M_PI/180);
        GLfloat y = centre + rad * sin(i*M_PI/180);
        vertices[int(i*8)] = x;
        vertices[int(i*8+1)] = y;
        vertices[int(i*8+2)] = 0.0f;
        vertices[int(i*8+3)] = 0.2f;
        vertices[int(i*8+4)] = 0.0f;
        vertices[int(i*8+5)] = 0.0f;
        vertices[int(i*8+6)] = x*2+0.5;
        vertices[int(i*8+7)] = y*2+0.5;
        i+= (360/N);
    }

    for (int i = 0; i < N; ++i)
    {
        indices[i*2] = i;
        indices[i*2+1] = i+1;
    }
    indices[N*2-1] = 0;
}


