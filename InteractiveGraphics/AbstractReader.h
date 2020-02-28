#pragma once
#ifndef ABSTRACT_READER
#define ABSTRACT_READER
#include <string>
using std::string;

class AbstractReader
{
protected:
   string _error;

public:
   AbstractReader() : _error("OK") {}
   virtual ~AbstractReader() {}
   virtual bool Read() = 0;
   virtual string ReportErrors() { return _error; }
};

#endif

