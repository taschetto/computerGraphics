#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <map>
#include <stack>
#include "Maze.h"

using namespace std;

Maze::Maze(size_t height, size_t width)
  : height(height)
  , width(width)
  , initial(nullptr)
  , goal(nullptr)
{
  grid = new Cell*[height]();
  for (size_t y = 0; y < height; y++)
    grid[y] = new Cell[width]();

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      grid[y][x].SetY(y);
      grid[y][x].SetX(x);
    }
  }

  Generate();
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

std::vector<Cell*> Maze::Cells()
{
  std::vector<Cell*> cells;

  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      cells.push_back(&grid[y][x]);
    }
  }

  return cells;
}

Cell* Maze::At(size_t x, size_t y)
{
  return &grid[y][x];
}

Cell* Maze::GetInitial()
{
  return initial;
}

Cell* Maze::GetGoal()
{
  return goal;
}

void Maze::Generate()
{
  std::map<Direction, size_t> Dx = { { North, 0 }, { South, 0 }, { East, 1 }, { West, -1 } };
  std::map<Direction, size_t> Dy = { { North, -1 }, { South, 1 }, { East, 0 }, { West, 0 } };
  std::map<Direction, Direction> Oposite = { { North, South }, { South, North }, { East, West }, { West, East } };

  std::srand((unsigned int)std::time(0));
  Cell* initial = &grid[std::rand() % height][std::rand() % width];
  initial->Visit();

  this->initial = initial;

  stack<Cell*> cells;
  cells.push(initial);
  
  while (cells.size() > 0)
  {
    Cell* cell = cells.top();
    
    size_t y = cell->GetY();
    size_t x = cell->GetX();

    std::vector<Direction> directions = { North, South, East, West };
    std::random_shuffle(directions.begin(), directions.end());

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

        cells.push(&grid[ny][nx]);

        this->goal = &grid[ny][nx];

        break;
      }
    }
    if (!any) cells.pop();
  }
}