#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

float totvertices[14*36];

float vertices1[] = {
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
   };
   float vertices2[] = {
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
   };
   float vertices3[] = {
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
   };
   float vertices4[] = {
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
   };
   float vertices5[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
   };
   float vertices6[] = {
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
        glm::vec3( 0.6f, -3.3f, -3.0f),
        glm::vec3(-2.0f,  2.0f, 3.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };


class Cube {
    public:
        // the vertices are in world coordinates directly
        int vertex_count = 36;
        GLuint VAO;
        GLuint VBO;
        // this contains texture coordinates where the entire texture is sampled to a particular face
        Cube(bool texture=false){

            find(vertices1, 0);
            find(vertices2, 1);
            find(vertices3, 2);
            find(vertices4, 3);
            find(vertices5, 4);
            find(vertices6, 5);
            
            
            bind(texture);
        }
        void bind(bool texture){
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);

            glBindVertexArray(VAO);
            
             glBindBuffer( GL_ARRAY_BUFFER, VBO );
             glBufferData( GL_ARRAY_BUFFER, sizeof( totvertices ), totvertices, GL_STATIC_DRAW );
             glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 14* sizeof( GLfloat ), (GLvoid * ) 0 );
             glEnableVertexAttribArray( 0 );
             glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, 14* sizeof( GLfloat ), (GLvoid * ) (3* sizeof( GLfloat )));
             glEnableVertexAttribArray( 1 );
             glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, 14* sizeof( GLfloat ), (GLvoid * ) (6* sizeof( GLfloat )));
             glEnableVertexAttribArray( 2 );
             glVertexAttribPointer( 3, 3, GL_FLOAT, GL_FALSE, 14* sizeof( GLfloat ), (GLvoid * ) (8* sizeof( GLfloat )));
             glEnableVertexAttribArray( 3 );
             glVertexAttribPointer( 4, 3, GL_FLOAT, GL_FALSE, 14* sizeof( GLfloat ), (GLvoid * ) (11* sizeof( GLfloat )));
             glEnableVertexAttribArray( 4 );

             glBindBuffer( GL_ARRAY_BUFFER, 0 );
             glBindVertexArray(0);
            
        }
    void find(float *vertices, int no)
    {
            glm::vec3 pos1(vertices[0], vertices[1], vertices[2]);
            glm::vec3 pos2(vertices[8], vertices[9], vertices[10]);
            glm::vec3 pos3(vertices[16], vertices[17], vertices[18]);
            glm::vec3 pos4(vertices[32], vertices[33], vertices[34]);
            // texture coordinates
            glm::vec2 uv1(vertices[6], vertices[7]);
            glm::vec2 uv2(vertices[14], vertices[15]);
            glm::vec2 uv3(vertices[22], vertices[23]);
            glm::vec2 uv4(vertices[38], vertices[39]);
            // normal vector
            glm::vec3 nm(vertices[3],vertices[4], vertices[5]);

            // calculate tangent/bitangent vectors of both triangles
            glm::vec3 tangent1, bitangent1;
            glm::vec3 tangent2, bitangent2;
            // triangle 1
            // ----------
            glm::vec3 edge1 = pos2 - pos1;
            glm::vec3 edge2 = pos3 - pos1;
            glm::vec2 deltaUV1 = uv2 - uv1;
            glm::vec2 deltaUV2 = uv3 - uv1;

            GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

            tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
            tangent1 = glm::normalize(tangent1);

            bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
            bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
            bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
            bitangent1 = glm::normalize(bitangent1);

            // triangle 2
            // ----------
            edge1 = pos3 - pos1;
            edge2 = pos4 - pos1;
            deltaUV1 = uv3 - uv1;
            deltaUV2 = uv4 - uv1;

            f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

            tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
            tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
            tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
            tangent2 = glm::normalize(tangent2);


            bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
            bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
            bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
            bitangent2 = glm::normalize(bitangent2);


            float quadVertices[] =
            {
                // positions            // normal         // texcoords  // tangent                          // bitangent
                pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
                pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
                pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,

                pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
                pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
                pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
            };
            for (int i = 0; i < 14*6; ++i)
            {
                /* code */
                totvertices[no*14*6 + i] = quadVertices[i];
            }
    }
};
