#pragma once
#ifndef GRAPHICS_STRUCTURES
#define GRAPHICS_STRUCTURES

struct RGBA {
   float red, green, blue, alpha;
};

struct Vector {
   float x, y, z;
};

struct Vertex {
   float x, y, z;
   float red, green, blue;
};

#endif
