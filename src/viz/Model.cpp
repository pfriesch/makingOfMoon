#include "Model.hpp"

#include "../common.hpp"

using namespace std;
using namespace glm;

void Model::loadVertexData(vector<vec3> vertices, GLint shader, string vertexAttributeName)
{
    nVertices = vertices.size();
    vertexBuffer = new float[vertices.size()*3];
    for(int i = 0; i < nVertices; i++)
    {
        vertexBuffer[i*3] = vertices[i].x;
        vertexBuffer[i*3+1] = vertices[i].y;
        vertexBuffer[i*3+2] = vertices[i].z;
    }

    GLint vertexAttributeLocation = glGetAttribLocation(shader, vertexAttributeName.c_str());

    glGenVertexArrays(1, &vertexArrayObjectId);
    glBindVertexArray(vertexArrayObjectId);
    glGenBuffers(1, &vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, nVertices * 3 * sizeof(GLfloat), vertexBuffer, GL_STATIC_DRAW);
    glVertexAttribPointer(vertexAttributeLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(vertexAttributeLocation);
}

void Model::drawSolid()
{
    glBindVertexArray(vertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
}

void Model::drawWireframe()
{
    glBindVertexArray(vertexArrayObjectId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLES, 0, nVertices);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Model::freeVertexData()
{
    // Free data from GPU ...


    delete[] vertexBuffer;
}
