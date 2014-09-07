#include "Cell.h"

Cell::Cell()
: visited(false), order(0)
{
  walls.insert(North);
  walls.insert(South);
  walls.insert(East);
  walls.insert(West);
}

Cell::~Cell()
{
}

void Cell::SetY(size_t ny)
{
  y = ny;
}

void Cell::SetX(size_t nx)
{
  x = nx;
}

size_t Cell::GetY()
{
  return y;
}

size_t Cell::GetX()
{
  return x;
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

std::set<Direction> Cell::GetWalls()
{
  return walls;
}

bool Cell::HasWall(Direction direction)
{
  return walls.find(direction) != walls.end();
}