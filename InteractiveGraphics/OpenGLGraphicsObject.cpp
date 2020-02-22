#include "OpenGLGraphicsObject.h"

OpenGLGraphicsObject::~OpenGLGraphicsObject()
{
   glDeleteVertexArrays(1, &_vaoId);
   if (_objectData != nullptr) {
      delete[] _objectData;
   }
}

void OpenGLGraphicsObject::Setup()
{
   glGenVertexArrays(1, &_vaoId);
   glBindVertexArray(_vaoId);
   // Declare the buffer object and store a handle to the object
   glGenBuffers(1, &_vboId);
   // Bind the object to the binding target
   glBindBuffer(GL_ARRAY_BUFFER, _vboId);
   // Allocate memory in the GPU for the buffer bound to the binding target and then
   // copy the data
   glBufferData(GL_ARRAY_BUFFER, _arraySize * sizeof(Vertex), _objectData, GL_STATIC_DRAW);
   // Good practice to cleanup by unbinding 
   glBindBuffer(GL_ARRAY_BUFFER, 0);
   glBindVertexArray(0);
}

void OpenGLGraphicsObject::Render()
{
   glBindVertexArray(_vaoId);
   _shader->Select();


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
   glDrawArrays(GL_TRIANGLES, 0, _arraySize);

   glDisableVertexAttribArray(0);
   glDisableVertexAttribArray(1);
   glUseProgram(0);
   glBindVertexArray(0);
}
