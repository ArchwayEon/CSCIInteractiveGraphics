#include "OpenGLIndexedGraphicsObject.h"
#include "GLSLGraphicsShader.h"

void OpenGLIndexedGraphicsObject::Setup()
{
   glGenVertexArrays(1, &_vaoId);
   glBindVertexArray(_vaoId);
   glGenBuffers(1, &_vboId);
   glGenBuffers(1, &_indexVbo);
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVbo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexes.size() * sizeof(unsigned int),
      &_indexes[0], GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

void OpenGLIndexedGraphicsObject::Render()
{
   auto shader = (GLSLGraphicsShader*)_shader;
   shader->Select();

   shader->SendMatricesToGPU();
   shader->SendMatrixToGPU("world", frame.orientation);

   glBindVertexArray(_vaoId);
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   // Positions
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(
      0,
      3,              // Each position has 3 components
      GL_FLOAT,       // Each component is a 32-bit floating point value
      GL_FALSE,
      sizeof(Vertex), // The number of bytes to the next position
      (void*)0        // Byte offset of the first position in the array
   );
   // Colors
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(
      1,
      3,                          // Each color has 3 components
      GL_FLOAT,                   // Each component is a 32-bit floating point value
      GL_FALSE,
      sizeof(Vertex),             // The number of bytes to the next color
      (void*)(sizeof(GLfloat) * 3) // Byte offset of the first color in the array
   );
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexVbo);
   glDrawElements(GL_TRIANGLES, (GLsizei)_indexes.size(), GL_UNSIGNED_INT, 0);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}
