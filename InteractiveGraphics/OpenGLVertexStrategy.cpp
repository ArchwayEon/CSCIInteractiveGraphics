#include "OpenGLVertexStrategy.h"
#include <glad\glad.h>
#include <vector>
using std::vector;

void OpenGLVertexStrategy::SetBufferInterpretation(
   unsigned int location, unsigned int count, 
   unsigned int bytesToNext, unsigned char offset)
{
   glEnableVertexAttribArray(location);
   glVertexAttribPointer(
      location,
      count,        // Number of components
      GL_FLOAT,     // Each component is a 32-bit floating point value
      GL_FALSE,
      bytesToNext,  // The number of bytes to the next item
      (void*)offset // Byte offset of the first item in the array
   );
}
