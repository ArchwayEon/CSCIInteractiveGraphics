#pragma once
#ifndef GLSL_GRAPHICS_SHADER
#define GLSL_GRAPHICS_SHADER

#include "AbstractGraphicsShader.h"


class GLSLGraphicsShader :
   public AbstractGraphicsShader
{
private:
   string _vertexSource, _fragmentSource;
   string _errorReport;
   GLuint _shaderProgram;

public:
   GLSLGraphicsShader(AbstractReader* reader) : 
      AbstractGraphicsShader(reader),
      _shaderProgram(0), _errorReport("OK"), 
      _vertexSource(""), _fragmentSource("") {}
   ~GLSLGraphicsShader() {}
   void SetUpDefaultSources();
   bool ReadShaderSources(const string& vertexFilePath, const string& fragmentFilePath);
   bool ReadVertexShaderSource(const string& filePath);
   bool ReadFragmentShaderSource(const string& filePath);
   string ReportErrors();
   bool Create();
   void Select();

private:
   GLuint CompileShader(GLenum type, const GLchar* source);
   GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, 
      PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};

#endif

