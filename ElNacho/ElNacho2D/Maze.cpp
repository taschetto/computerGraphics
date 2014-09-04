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

void Maze::Generate()
{
  stack<MazeCell> cells;
  cells.push(grid[rand() % height][rand() % width]);

  while (cells.size() > 0)
  {
    MazeCell cell = cells.top();
    cells.pop();

    size_t y = cell.GetY();
    size_t x = cell.GetX();

    std::vector<Direction> directions = { North, South, East, West };

    unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(directions.begin(), directions.end(), std::default_random_engine(seed));

    for (Direction d : directions)
    {
      size_t ny = y + Dy[d];
      size_t nx = x + Dx[d];

      if (nx >= 0 && ny >= 0 && nx < width && ny < height && !grid[ny][nx].IsVisited())
      {
        grid[ny][nx].Visit();

        grid[y][x].Carve(d);
        grid[ny][nx].Carve(Oposite[d]);

        cells.push(grid[ny][nx]);

        break;
      }
    }
  }
}

void Maze::Print()
{
  for (size_t y = 0; y < height; y++)
  {
    for (size_t x = 0; x < width; x++)
    {
      MazeCell cell = grid[y][x];

      cout << y << "," << x << ":";

      for (Direction d : cell.GetWalls())
      {
        cout << " " << d;
      }

      cout << endl;
    }
  }
}
