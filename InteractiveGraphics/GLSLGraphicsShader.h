#pragma once
#ifndef GLSL_GRAPHICS_SHADER
#define GLSL_GRAPHICS_SHADER

#include <glm/glm.hpp>
#include "AbstractGraphicsShader.h"

class GLSLGraphicsShader :
   public AbstractGraphicsShader
{
private:
   string _vertexSource, _fragmentSource;
   string _errorReport;
   GLuint _shaderProgram;

public:
   glm::mat4 view, projection;

public:
   GLSLGraphicsShader(AbstractReader* reader) : 
      AbstractGraphicsShader(reader),
      _shaderProgram(0), _errorReport("OK"), 
      _vertexSource(""), _fragmentSource(""), 
      view(1.0), projection(1.0) {}
   ~GLSLGraphicsShader() {}
   void SetUpDefaultSources();
   bool ReadShaderSources(const string& vertexFilePath, const string& fragmentFilePath);
   bool ReadVertexShaderSource(const string& filePath);
   bool ReadFragmentShaderSource(const string& filePath);
   string ReportErrors();
   bool Create();
   void Select();
   void SendMatrixToGPU(const string& uniformName, const glm::mat4& matrix);
   void SendMatricesToGPU();

private:
   GLuint CompileShader(GLenum type, const GLchar* source);
   GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, 
      PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};

#endif

