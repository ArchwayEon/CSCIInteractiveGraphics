#pragma once
#ifndef ABSTRACT_GRAPHICS_SHADER
#define ABSTRACT_GRAPHICS_SHADER
#include <string>
using std::string;

class AbstractGraphicsShader
{
public:
   AbstractGraphicsShader() {}
   virtual ~AbstractGraphicsShader() {}
   virtual void SetUpDefaultSource() = 0;
   virtual void LoadVertexSourceFromFile(const string& filePath) = 0;
   virtual void LoadFragmentSourceFromFile(const string& filePath) = 0;
   virtual string ReportErrors() = 0;
   virtual bool Create() = 0;
   virtual void Select() = 0;
};

#endif

