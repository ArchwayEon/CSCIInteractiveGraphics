#include "GraphicsObjectReader.h"
#include "OpenGLVertexPCStrategy.h"
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
   _object->vertexStrategy = new OpenGLVertexPCStrategy();
   auto vertexStrategy = (OpenGLVertexPCStrategy*)_object->vertexStrategy;
   float x, y, z, red, green, blue;
   while (!fin.eof()) {
      fin >> x >> y >> z >> red >> green >> blue;
      vertexStrategy->AddVertex({x, y, z, red, green, blue});
   }
   fin.close();
   return true;
}
