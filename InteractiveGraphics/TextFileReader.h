#pragma once
#ifndef TEXT_FILE_READER
#define TEXT_FILE_READER
#include "AbstractReader.h"

class TextFileReader :
   public AbstractReader
{
private:
   string _filePath;
   string _data;

public:
   TextFileReader() :
      AbstractReader(), _filePath("") {}
   ~TextFileReader() {}
   void SetFilePath(const string& filePath) { _filePath = filePath; }
   string GetData() { return _data; }
   bool Read();
private:
   void Trim(string& str);
};

#endif

