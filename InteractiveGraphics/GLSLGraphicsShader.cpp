#include <glad\glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "GLSLGraphicsShader.h"
#include <sstream>
#include <fstream>
#include "TextFileReader.h"
using std::stringstream;
using std::ifstream;

void GLSLGraphicsShader::SetUpDefaultSources()
{
   _vertexSource =
      "#version 400\n"\
      "layout(location = 0) in vec3 position;\n"\
      "layout(location = 1) in vec3 vertexColor;\n"\
      "out vec4 fragColor;\n"\
      "void main()\n"\
      "{\n"\
      "   gl_Position = vec4(position, 1.0)\n" \
      "   fragColor = vec4(vertexColor, 1.0);\n" \
      "}\n";

   _fragmentSource =
      "#version 400\n"\
      "in vec4 fragColor;\n"\
      "out vec4 color;\n"\
      "void main()\n"\
      "{\n"\
      "   color = fragColor;\n"\
      "}\n";
}

bool GLSLGraphicsShader::ReadShaderSources(const string& vertexFilePath, const string& fragmentFilePath)
{
   if (!ReadVertexShaderSource(vertexFilePath)) {
      return false;
   }
   if (!ReadFragmentShaderSource(fragmentFilePath)) {
      return false;
   }
   return true;
}

bool GLSLGraphicsShader::ReadVertexShaderSource(const string& filePath)
{
   TextFileReader* reader = (TextFileReader*)_reader;
   reader->SetFilePath(filePath);
   bool result = reader->Read();
   if (result) {
      _vertexSource = reader->GetData();
   }
   return result;
}

bool GLSLGraphicsShader::ReadFragmentShaderSource(const string& filePath)
{
   TextFileReader* reader = (TextFileReader*)_reader;
   reader->SetFilePath(filePath);
   bool result = reader->Read();
   if (result) {
      _fragmentSource = reader->GetData();
   }
   return result;
}

string GLSLGraphicsShader::ReportErrors()
{
   return _errorReport;
}

bool GLSLGraphicsShader::Create()
{
   GLuint vertexShader = 
      CompileShader(GL_VERTEX_SHADER, _vertexSource.c_str());
   if (vertexShader == 0) return false;
   GLuint fragmentShader = 
      CompileShader(GL_FRAGMENT_SHADER, _fragmentSource.c_str());
   if (fragmentShader == 0) return false;
   _shaderProgram = LinkShader(vertexShader, fragmentShader);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   if (_shaderProgram == 0) return false;
   return true;
}

void GLSLGraphicsShader::Select()
{
   glUseProgram(_shaderProgram);
}

void GLSLGraphicsShader::SendMatrixToGPU(const string& uniformName, const glm::mat4& matrix)
{
   unsigned int uniformLocation = glGetUniformLocation(_shaderProgram, uniformName.c_str());
   glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLSLGraphicsShader::SendMatricesToGPU()
{
   SendMatrixToGPU("view", view);
   SendMatrixToGPU("projection", projection);
}

void GLSLGraphicsShader::SendFloatToGPU(const string& name, float data) const
{
   unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniform1f(location, data);
}

void GLSLGraphicsShader::SendIntegerToGPU(const string& name, int data) const
{
   unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniform1i(location, data);
}

void GLSLGraphicsShader::SendVector3ToGPU(const string& name, const glm::vec3& vector) const
{
   unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniform3fv(location, 1, glm::value_ptr(vector));
}

void GLSLGraphicsShader::SendFloatArrayToGPU(const string& name, void* values, unsigned int count) const
{
   unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniform1fv(location, count, (float*)values);
}

void GLSLGraphicsShader::SendVectorArrayToGPU(const string& name, void* vectorArray, unsigned int count) const
{
   unsigned int location = glGetUniformLocation(_shaderProgram, name.c_str());
   glUniform3fv(location, count, (float*)vectorArray);
}

void GLSLGraphicsShader::SendGlobalLightToGPU(const glm::vec3& position, const glm::vec3& color, float intensity) const
{
   SendVector3ToGPU("globalLightPosition", position);
   SendVector3ToGPU("globalLightColor", color);
   SendFloatToGPU("globalLightIntensity", intensity);
}

void GLSLGraphicsShader::SendLocalLightToGPU(
   const glm::vec3& position, const glm::vec3& color, 
   float intensity, float attenuationCoefficient) const
{
   SendVector3ToGPU("localLightPosition", position);
   SendVector3ToGPU("localLightColor", color);
   SendFloatToGPU("localLightIntensity", intensity);
   SendFloatToGPU("localLightAttenuationCoefficient", attenuationCoefficient);
}

void GLSLGraphicsShader::SendLocalLightDataToGPU(size_t numberOfLights, glm::vec3 positions[], glm::vec3 colors[], float intensities[], float attenuationCoefficients[]) const
{
   SendIntegerToGPU("numberOfLights", (int)numberOfLights);
   SendVectorArrayToGPU("localLightPosition", positions, (int)numberOfLights);
   SendVectorArrayToGPU("localLightColor", colors, (int)numberOfLights);
   SendFloatArrayToGPU("localLightIntensity", intensities, (int)numberOfLights);
   SendFloatArrayToGPU("localLightAttenuationCoefficient", attenuationCoefficients, (int)numberOfLights);
}

GLuint GLSLGraphicsShader::CompileShader(GLenum type, const GLchar* source)
{
   GLint length = (GLint)(sizeof(GLchar) * strlen(source));
   GLuint shader = glCreateShader(type);
   glShaderSource(shader, 1, (const GLchar**)&source, &length);
   glCompileShader(shader);
   GLint shaderOk = 0;
   glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderOk);
   if (!shaderOk) {
      LogError(shader, glGetShaderiv, glGetShaderInfoLog);
      glDeleteShader(shader);
      shader = 0;
   }
   return shader;
}

GLuint GLSLGraphicsShader::LinkShader(GLuint vertexShader, GLuint fragmentShader)
{
   GLuint program = glCreateProgram();
   glAttachShader(program, vertexShader);
   glAttachShader(program, fragmentShader);
   glLinkProgram(program);
   GLint programOk = 0;
   glGetProgramiv(program, GL_LINK_STATUS, &programOk);
   if (!programOk) {
      LogError(program, glGetProgramiv, glGetProgramInfoLog);
      glDeleteShader(program);
      program = 0;
   }
   return program;
}

void GLSLGraphicsShader::LogError(GLuint shader, PFNGLGETSHADERIVPROC glGet__iv, PFNGLGETSHADERINFOLOGPROC glGet__InfoLog)
{
   GLint logLength;
   glGet__iv(shader, GL_INFO_LOG_LENGTH, &logLength);
   char* info = (char*)malloc(logLength);
   glGet__InfoLog(shader, logLength, NULL, info);
   stringstream ss;
   ss << info;
   getline(ss, _errorReport);
   free(info);
}

