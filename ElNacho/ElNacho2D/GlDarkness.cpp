#include "GlGoal.h"
#include "GlDarkness.h"

GlDarkness::GlDarkness(Nacho* nacho, float left, float right, float bottom, float top)
  : nacho(nacho)
  , left(left)
  , right(right)
  , bottom(bottom)
  , top(top)
{
}

GlDarkness::~GlDarkness()
{
}

void GlDarkness::Scale()
{
}

void GlDarkness::Translate()
{
}

void GlDarkness::Draw()
{
  glColor3f(1, 1, 0);
  glLineWidth(2);
  glBegin(GL_QUADS);
  glVertex2f(0.2f, 0.2f);
  glVertex2f(0.2f, 0.8f);
  glVertex2f(0.8f, 0.8f);
  glVertex2f(0.8f, 0.2f);
  glEnd();
}