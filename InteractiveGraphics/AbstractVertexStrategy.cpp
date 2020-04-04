#include "AbstractVertexStrategy.h"
#include "PolygonMesh.h"
#include "GraphicsStructures.h"

AbstractVertexStrategy::AbstractVertexStrategy(AbstractMesh* mesh)
{
   _mesh = mesh;
   if (_mesh == nullptr) {
      _mesh = new PolygonMesh<VertexPCNT>();
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
