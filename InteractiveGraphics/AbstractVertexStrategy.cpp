#include "AbstractVertexStrategy.h"
#include "PolygonMesh.h"

AbstractVertexStrategy::AbstractVertexStrategy(AbstractMesh* mesh)
{
   _mesh = mesh;
   if (_mesh == nullptr) {
      _mesh = new PolygonMesh();
   }
}

AbstractVertexStrategy::~AbstractVertexStrategy()
{
   if (_mesh != nullptr) {
      delete _mesh;
   }
}

void AbstractVertexStrategy::SetMesh(AbstractMesh* mesh)
{
   _mesh = mesh;
}
