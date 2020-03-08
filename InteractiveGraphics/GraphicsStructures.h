#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES

struct RGBA {
   float red, green, blue, alpha;
};

struct Vector3 {
   float x, y, z;
};

struct Tex {
   float s, t;
};

// Vertex - Position, Color
struct VertexPC {
   float x, y, z;
   float red, green, blue;
};

// Vertex - Position, Color (RGBA), Texture
struct VertexPCT {
   Vector3 position;
   RGBA color;
   Tex tex;
};

#endif
