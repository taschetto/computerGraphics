#include "Cell.h"

Cell::Cell()
  : x(0)
  , y(0)
  , visited(false)
{
  walls.insert(North);
  walls.insert(South);
  walls.insert(East);
  walls.insert(West);
}

Cell::~Cell()
{
}

void Cell::SetX(size_t nx)
{
  x = nx;
}

void Cell::SetY(size_t ny)
{
  y = ny;
}

size_t Cell::GetX()
{
  return x;
}

size_t Cell::GetY()
{
  return y;
}

std::set<Direction> Cell::GetWalls()
{
  return walls;
}

bool Cell::IsVisited()
{
  return visited;
}

void Cell::Visit()
{
  visited = true;
}

void Cell::Carve(Direction direction)
{
  walls.erase(direction);
}

bool Cell::HasWall(Direction direction)
{
  return walls.find(direction) != walls.end();
}