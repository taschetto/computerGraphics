#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <stack>
#include <string>
#include "Maze.h"

using namespace std;

Maze::Maze(size_t height, size_t width)
  : height(height)
  , width(width)
{
  grid = new MazeCell*[height]();
  for (size_t y = 0; y < height; y++)
    grid[y] = new MazeCell[width]();

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      grid[y][x].SetY(y);
      grid[y][x].SetX(x);
    }
  }

  Dx[North] = 0;
  Dx[South] = 0;
  Dx[East] = 1;
  Dx[West] = -1;

  Dy[North] = -1;
  Dy[South] = 1;
  Dy[East] = 0;
  Dy[West] = 0;

  Oposite[North] = South;
  Oposite[South] = North;
  Oposite[East] = West;
  Oposite[West] = East;
}

Maze::~Maze()
{
  for (size_t y = 0; y < height; y++)
    delete[] grid[y];
  delete[] grid;
}

size_t Maze::GetWidth()
{
  return width;
}

size_t Maze::GetHeight()
{
  return height;
}

void Maze::Generate()
{
  MazeCell* initial = &grid[rand() % height][rand() % width];
  initial->Visit();
  int order = 1;
  initial->SetOrder(order++);

  stack<MazeCell*> cells;
  cells.push(initial);
  while (cells.size() > 0)
  {
    MazeCell* cell = cells.top();
    
    size_t y = cell->GetY();
    size_t x = cell->GetX();

    std::vector<Direction> directions = { North, South, East, West };

    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

    bool any = false;
    for (Direction d : directions)
    {
      size_t ny = y + Dy[d];
      size_t nx = x + Dx[d];

      if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].IsVisited())
      {
        any = true;
        grid[ny][nx].Visit();

        grid[y][x].Carve(d);
        grid[ny][nx].Carve(Oposite[d]);

        grid[ny][nx].SetOrder(order++);

        cells.push(&grid[ny][nx]);

        break;
      }
    }
    if (!any) cells.pop();
  }
}

std::vector<MazeCell*> Maze::Cells()
{
  std::vector<MazeCell*> cells;

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      cells.push_back(&grid[y][x]);
    }
  }

  return cells;
}

void Maze::Dump()
{
  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      cout << x << "," << y << " ... ";
      if (grid[y][x].HasWall(North)) cout << 'N';
      if (grid[y][x].HasWall(South)) cout << 'S';
      if (grid[y][x].HasWall(West)) cout << 'W';
      if (grid[y][x].HasWall(East)) cout << 'E';
      cout << endl;
    }
  }
}