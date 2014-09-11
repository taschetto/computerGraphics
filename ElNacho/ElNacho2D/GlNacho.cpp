#include "GlNacho.h"
#include "OpenGL.h"
#include "Nacho.h"

#include <vector>

GlNacho::GlNacho(Maze* maze, Nacho* nacho)
: maze(maze)
, nacho(nacho)
{
}

GlNacho::~GlNacho()
{
}

float GlNacho::GetTx()
{
  return (float)nacho->GetX();
}

float GlNacho::GetTy()
{
  return maze->GetHeight() - (float)nacho->GetY() - 1;
}

void GlNacho::DrawCircle(float centerX, float centerY, float radius, int segments)
{
  std::vector<std::pair<float, float>> vertexes;
  for (int i = 0; i <= segments; i++)
  {
    float theta = 2.0f * 3.1415926f * float(i) / float(segments);

    float x = radius * cosf(theta) + centerX;
    float y = radius * sinf(theta) + centerY;

    vertexes.push_back(std::make_pair(x, y));
  }

  glBegin(GL_TRIANGLE_FAN);
    glColor4f(0, 0, 0, 0);
    glVertex2f(centerX, centerY);
    glColor4f(0, 1, 0, 1);
    for (std::pair<float, float> pair : vertexes)
    {
      glVertex2f(pair.first, pair.second);
    }
  glEnd();

  glColor4f(0, 0, 0, 1);
  glBegin(GL_POLYGON);
    glVertex2f(centerX - radius, centerY + radius);
    glVertex2f(centerX, centerY + radius);
    DrawArc(centerX, centerY, radius, 3.1415926f / 2, 3.1415926f / 2, 4);
    glVertex2f(centerX - radius, centerY);
  glEnd();

  glColor4f(1, 0, 0, 1);
  glBegin(GL_LINE_LOOP);
  //glVertex2f(centerX - radius, centerY);
  DrawArc(centerX, centerY, radius, 3.1415926f, 3.1415926f / 2, 4);
  glVertex2f(centerX - radius, centerY - radius);
  glEnd();

  //glBegin(GL_TRIANGLE_STRIP);
  ////glBegin(GL_LINE_LOOP);
  //  glColor4f(1, 0, 0, 1);
  //  glVertex2f(centerX, centerY + radius);
  //  glVertex2f(centerX - radius, centerY + radius);
  //  glVertex2f(centerX - radius, centerY - radius);
  //  glVertex2f(centerX, centerY - radius);

  //  // arco esquerdo
  //  glVertex2f(centerX - radius + 0.1, centerY);
  //glEnd();

  //glBegin(GL_POLYGON);
  ////glBegin(GL_LINE_LOOP);
  //  glColor4f(0, 1, 0, 1);
  //  glVertex2f(centerX, centerY + radius);
  //  glVertex2f(centerX + radius, centerY + radius);
  //  glVertex2f(centerX + radius, centerY - radius);
  //  glVertex2f(centerX, centerY - radius);

  //  //arco direito
  //  glVertex2f(centerX + radius - 0.1, centerY);
  //glEnd();
}

void GlNacho::DrawArc(float cx, float cy, float r, float start_angle, float arc_angle, int num_segments)
{
  float theta = arc_angle / float(num_segments - 1);

  float tangetial_factor = tanf(theta);

  float radial_factor = cosf(theta);

  float x = r * cosf(start_angle);
  float y = r * sinf(start_angle);

  for (int ii = 0; ii < num_segments; ii++)
  {
    glVertex2f(x + cx, y + cy);

    float tx = -y;
    float ty = x;

    x += tx * tangetial_factor;
    y += ty * tangetial_factor;

    x *= radial_factor;
    y *= radial_factor;
  }
}

void GlNacho::Scale()
{
}

void GlNacho::Translate()
{
  glTranslatef(GetTx(), GetTy(), 0.f);
}

void GlNacho::Draw()
{
  glColor3f(1, 1, 0);
  glBegin(GL_TRIANGLES);
    glVertex2f(0.2f, 0.2f);
    glVertex2f(0.5f, 0.8f);
    glVertex2f(0.8f, 0.2f);
  glEnd();

  DrawCircle(0.5, 0.5, nacho->GetRadius() / 3, 16);
}