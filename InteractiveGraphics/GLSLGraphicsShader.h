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
   GLSLGraphicsShader() : 
      _shaderProgram(0), _errorReport("OK"), 
      _vertexSource(""), _fragmentSource("") {}
   ~GLSLGraphicsShader() {}
   void SetUpDefaultSource();
   void LoadVertexSourceFromFile(const string& filePath);
   void LoadFragmentSourceFromFile(const string& filePath);
   string ReportErrors();
   bool Create();
   void Select();

private:
   GLuint CompileShader(GLenum type, const GLchar* source);
   GLuint LinkShader(GLuint vertexShader, GLuint fragmentShader);
   void LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog);
};

#endif

