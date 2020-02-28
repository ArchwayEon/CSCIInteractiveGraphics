#include "GraphicsObjectReader.h"
#include <sstream>
#include <fstream>
using namespace std;

bool GraphicsObjectReader::Read()
{
   stringstream ss;
   ifstream fin;
   fin.open(_filePath.c_str());
   if (fin.fail()) {
      ss << "Could not open: " << _filePath << std::endl;
      getline(ss, _error);
      return false;
   }

   _object = new OpenGLGraphicsObject();
   float x, y, z, red, green, blue;
   while (!fin.eof()) {
      fin >> x >> y >> z >> red >> green >> blue;
      _object->AddVertex({x, y, z, red, green, blue});
   }
   fin.close();
   return true;
}
