#include <map>
#include "Nacho.h"

Nacho::Nacho(Maze* maze)
: maze(maze)
{
  x = maze->GetInitial()->GetX();
  y = maze->GetInitial()->GetY();
  radius = (float)maze->GetWidth() / 2.f;
}

Nacho::~Nacho()
{
}

size_t Nacho::GetX()
{
  return x;
}

size_t Nacho::GetY()
{
  return y;
}

void Nacho::Walk(Direction direction)
{
  std::map<Direction, size_t> Dx = { { North, 0 }, { South, 0 }, { East, 1 }, { West, -1 } };
  std::map<Direction, size_t> Dy = { { North, -1 }, { South, 1 }, { East, 0 }, { West, 0 } };
  std::map<Direction, Direction> Oposite = { { North, South }, { South, North }, { East, West }, { West, East } };

  Cell* cell = maze->At(x, y);

  if (!cell->HasWall(direction))
  {
    x += Dx[direction];
    y += Dy[direction];

    if (radius > 1.f)
      radius -= 0.1f;
  }
}
