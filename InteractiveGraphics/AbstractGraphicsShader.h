#pragma once
#ifndef ABSTRACT_GRAPHICS_SHADER
#define ABSTRACT_GRAPHICS_SHADER
#include <string>
#include <glm/glm.hpp>
#include "AbstractReader.h"
using std::string;

class AbstractGraphicsShader
{
protected:
   AbstractReader* _reader;

public:
   AbstractGraphicsShader(AbstractReader* reader) : _reader(reader) {}
   virtual ~AbstractGraphicsShader();
   virtual void SetUpDefaultSources() = 0;
   virtual bool ReadVertexShaderSource(const string& filePath) = 0;
   virtual bool ReadFragmentShaderSource(const string& filePath) = 0;
   virtual string ReportErrors() = 0;
   virtual bool Create() = 0;
   virtual void Select() = 0;
   virtual void SendFloatToGPU(const string& name, float data) const = 0;
   virtual void SendIntegerToGPU(const string& name, int data) const = 0;
   virtual void SendVector3ToGPU(const string& name, const glm::vec3& vector) const = 0;
   virtual void SendFloatArrayToGPU(const string& name, void* values, unsigned int count) const = 0;
   virtual void SendVectorArrayToGPU(const string& name, void* vectorArray, unsigned int count) const = 0;

   virtual void SendGlobalLightToGPU(
      const glm::vec3& position, const glm::vec3& color, float intensity) const = 0;
   virtual void SendLocalLightToGPU(
      const glm::vec3& position, const glm::vec3& color, 
      float intensity, float attenuationCoefficient) const = 0;
   virtual void SendLocalLightDataToGPU(
      size_t numberOfLights,
      glm::vec3 positions[], glm::vec3 colors[],
      float intensities[], float attenuationCoefficients[]) const = 0;
};

#endif

