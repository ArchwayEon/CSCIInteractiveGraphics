#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES

struct RGB {
   float red, green, blue;
};

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
// Vertex - Position, Color (RGBA), Normal, Texture
struct VertexPCNT {
   Vector3 position;
   RGBA color;
   Vector3 normal;
   Tex tex;
};

struct Material {
   float ambientIntensity; // Intensity of light applied to the object
};

struct Light {
   Vector3 position;
   RGB color;
   float intensity;
   float attenuationCoefficient;
};


#endif
