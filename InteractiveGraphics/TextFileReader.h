#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER
#include "AbstractReader.h"

class TextFileReader :
   public AbstractReader
{
private:
   string _filePath;

public:
   TextFileReader() :
      AbstractReader(), _filePath("") {}
   ~TextFileReader() {}
   void SetFilePath(const string& filePath) { _filePath = filePath; }
   bool Read(string& data);
private:
   void Trim(string& str);
};

#endif

