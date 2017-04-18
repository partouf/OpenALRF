#include "MapTypes.h"
#include <string>

OpenALRF::EMapCoordsOutOfBounds::EMapCoordsOutOfBounds(int X, int Y) : std::runtime_error("Map coordinates out of bounds")
{
   //this.X = X;
   //this.Y = Y;
}
