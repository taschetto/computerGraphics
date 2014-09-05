#include "MazeCell.h"

MazeCell::MazeCell()
: visited(false), order(0)
{
  walls.insert(North);
  walls.insert(South);
  walls.insert(East);
  walls.insert(West);
}

MazeCell::~MazeCell()
{
}

void MazeCell::SetY(size_t ny)
{
  y = ny;
}

void MazeCell::SetX(size_t nx)
{
  x = nx;
}

size_t MazeCell::GetY()
{
  return y;
}

size_t MazeCell::GetX()
{
  return x;
}

bool MazeCell::IsVisited()
{
  return visited;
}

void MazeCell::Visit()
{
  visited = true;
}

void MazeCell::Carve(Direction direction)
{
  walls.erase(direction);
}

std::set<Direction> MazeCell::GetWalls()
{
  return walls;
}

bool MazeCell::HasWall(Direction direction)
{
  return walls.find(direction) != walls.end();
}