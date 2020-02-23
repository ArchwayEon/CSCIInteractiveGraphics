#include "TextFileReader.h"
#include <sstream>
#include <fstream>
using namespace std;

bool TextFileReader::Read(string& data)
{
   stringstream ss;
   ifstream fin;
   fin.open(_filePath.c_str());
   if (fin.fail()) {
      ss << "Could not open: " << _filePath << std::endl;
      getline(ss, _error);
      return false;
   }

   string line;
   while (!fin.eof()) {
      getline(fin, line);
      Trim(line);
      if (line != "") { // Skip blank lines
         data += line + "\n";
      }
   }
   fin.close();
   return true;
}

void TextFileReader::Trim(string& str)
{
   const string delimiters = " \f\n\r\t\v";
   str.erase(str.find_last_not_of(delimiters) + 1);
   str.erase(0, str.find_first_not_of(delimiters));
}
