#pragma once
#ifndef OPENGL_GRAPHICS_OBJECT
#define OPENGL_GRAPHICS_OBJECT

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include "AbstractGraphicsObject.h"
#include "GraphicsStructures.h"
#include <vector>
using std::vector;

class OpenGLGraphicsObject :
   public AbstractGraphicsObject
{
private:
   GLuint _vaoId, _vboId;
   vector<Vertex> _vertices;

public:
   glm::mat4 orientation;

public:
   OpenGLGraphicsObject() : 
      _vaoId(0), _vboId(0), orientation(1.0)
   {}
   OpenGLGraphicsObject(AbstractGraphicsShader* shader) : 
      AbstractGraphicsObject(shader), _vaoId(0), _vboId(0), orientation(1.0)
   {}
   ~OpenGLGraphicsObject();
   void AddVertex(const Vertex& vertex) { _vertices.push_back(vertex); }
   void Setup();
   void Render();
   void Rotate(float degrees, const glm::vec3& axis);
   void RotateWorld(float degrees, const glm::vec3& axis);
   void Move(const glm::vec3& vector);
};

#endif

