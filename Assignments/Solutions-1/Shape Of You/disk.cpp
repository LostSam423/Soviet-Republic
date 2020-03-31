

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>

#include "shader.hpp"
#include "readfile.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void drawDisk(GLfloat *indices, GLuint *poi, int N);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;
const int N = 360;

 
int main()
{
    GLfloat indices[N*3];
    GLuint poi[N*3];
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
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
    
    glViewport(0, 0,SCR_WIDTH, SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    drawDisk(indices, poi, N);
    Shader *shdr = new Shader("shad.vs","shad.fs");    
    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers( 1, &VBO );
    
    
    glBindVertexArray( VAO );

    glBindBuffer( GL_ARRAY_BUFFER, VBO );
    glBufferData( GL_ARRAY_BUFFER, sizeof( indices ), indices, GL_STATIC_DRAW );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 3* sizeof( GLfloat ), (GLvoid * ) 0 );
    glEnableVertexAttribArray( 0 );
    
    glGenBuffers( 1, &EBO);
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, EBO );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(poi), poi, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
        
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        shdr->use();

        glBindVertexArray( VAO );

        glDrawElements(GL_TRIANGLES, N*3, GL_UNSIGNED_INT, 0);

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

void drawDisk(GLfloat *indices, GLuint *poi, int N)
{
    GLfloat centre = 0.0f;
    GLfloat rad = 0.2f;

    for(int i=0; i<=N; i+=360/N){
        GLfloat x = centre + rad * cos(i*M_PI/180);
        GLfloat y = centre + rad * sin(i*M_PI/180);
        indices[i*3] = x;
        indices[i*3+1] = y;
        indices[i*3+2] = 0.0f;
    }   
    indices[N*3] = centre;
    indices[N*3+1] = centre;
    indices[N*3+2] = centre;
    for (int i = 0; i < N; ++i)
    {
        poi[i*3] = N;
        poi[i*3+1] = i;
        poi[i*3+2] = i+1;
    }
    poi[N*3-1] = 0;
}


