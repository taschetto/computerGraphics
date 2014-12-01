#include <vector>
#include "PlayState.h"
#include "GlCell.h"
#include "GlInitial.h"
#include "GlGoal.h"
#include "GlNacho.h"
#include "GlBattery.h"
#include "IDrawable.h"
#include "Maze.h"
#include "Nacho.h"
#include "OpenGL.h"
#include "WinState.h"
#include <math.h>

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat light_position[] = { 0.0f, 5.0f, 0.0f, 0.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

PlayState *PlayState::instance = 0;

void PlayState::Init()
{
  maze = new Maze(level + 4);
  nacho = new Nacho(maze);
  
  glClearColor(0, 0, 0, 1);

  SetLights();

  for (Cell* cell : maze->Cells()) drawables.push_back(new GlCell(maze, cell));

  for (Cell* cell : maze->GetBatteries()) batteries.push_back(new GlBattery(maze, cell));
  drawables.push_back(new GlInitial(maze, maze->GetInitial()));
  drawables.push_back(new GlGoal(maze, maze->GetGoal()));
  drawables.push_back(new GlNacho(maze, nacho));
}

void PlayState::Cleanup()
{
  for (IDrawable* drawable : drawables)
    delete drawable;
  drawables.clear();

  for (IDrawable* drawable : batteries)
    delete drawable;
  batteries.clear();

  delete maze;
  delete nacho;
}

void PlayState::Pause()
{
}

void PlayState::Resume()
{
}

void PlayState::HandleEvents(GameEngine* engine)
{
  Cell* goal = maze->GetGoal();

  if (nacho->GetX() == goal->GetX() && nacho->GetY() == goal->GetY())
  {
    Cleanup();
    level++;
    Init();

    engine->ChangeState(WinState::Instance());
    ::glutPostRedisplay();
  }

  // posteriormente substituir o vector de batteries por uma estrutura de dados mais adequada
  // quem sabe um dicionário com chave sendo uma tupla?
  for (Cell* cell : maze->GetBatteries())
  {
    if (nacho->GetX() == cell->GetX() && nacho->GetY() == cell->GetY())
    {
      maze->RemoveBattery(cell);
      nacho->SetRadius(nacho->GetRadius() * 2);

      for (IDrawable* drawable : batteries)
        delete drawable;
      batteries.clear();

      for (Cell* cell : maze->GetBatteries()) batteries.push_back(new GlBattery(maze, cell));
      ::glutPostRedisplay();
    }
  }
}

void PlayState::Draw()
{
  light_position[0] = maze->GetWidth() / 2.0f;
  light_position[1] = maze->GetWidth() / 2.0f;

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  SetVisualizationParams();

  for (IDrawable* drawable : drawables)
  {
    glPushMatrix();
    drawable->Translate();
    drawable->Scale();
    drawable->Draw();
    glPopMatrix();
  }

  for (IDrawable* drawable : batteries)
  {
    glPushMatrix();
    drawable->Translate();
    drawable->Scale();
    drawable->Draw();
    glPopMatrix();
  }

  glutSwapBuffers();
}

void PlayState::Keyboard(GameEngine*, unsigned char, int, int)
{
}

void PlayState::SpecialFunc(GameEngine*, int key, int, int)
{
  switch (key)
  {
  case GLUT_KEY_DOWN:
    if (view_option == 0) nacho->Walk(North);
    else if (view_option == 1) nacho->Walk(West);
    else if (view_option == 2) nacho->Walk(East);
    else if (view_option == 3) nacho->Walk(South);
    break;

  case GLUT_KEY_UP:
    if (view_option == 0) nacho->Walk(South);
    else if (view_option == 1) nacho->Walk(East);
    else if (view_option == 2) nacho->Walk(West);
    else if (view_option == 3) nacho->Walk(North);
    break;

  case GLUT_KEY_RIGHT:
    if (view_option == 0) nacho->Walk(East);
    else if (view_option == 1) nacho->Walk(North);
    else if (view_option == 2) nacho->Walk(South);
    else if (view_option == 3) nacho->Walk(West);
    break;

  case GLUT_KEY_LEFT:
    if (view_option == 0) nacho->Walk(West);
    else if (view_option == 1) nacho->Walk(South);
    else if (view_option == 2) nacho->Walk(North);
    else if (view_option == 3) nacho->Walk(East);
    break;

  case GLUT_KEY_F1:
    ++view_option %= 4;
    break;
  }
}

void PlayState::ReshapeFunc(GameEngine*, GLsizei w, GLsizei h)
{
  // Para previnir uma divisão por zero
  if (h == 0) h = 1;

  // Especifica as dimensões da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  SetVisualizationParams();
}

void PlayState::SetVisualizationParams()
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle, fAspect, 0.5, 500);
  SetObserverPosition();
}

void PlayState::SetObserverPosition()
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  float dist = sqrt(level / 3.0) + 5 + level;
  float toX = maze->GetWidth() / 2, toY = 0.0f, toZ = maze->GetWidth() / 2;

  posY = sqrt(level / 3.0) + 5 + level;

  float targetX = sqrt(level / 3.0) + 5 + level;
  float targetZ = sqrt(level / 3.0) + 5 + level;

  switch (view_option)
  {
  case 0:
    break;
  case 1:
    targetX *= -0.5;
    break;
  case 2:
    targetZ *= -1 / 2;
    break;
  case 3:
    targetX *= -0.5;
    targetZ *= -0.5;
    break;
  }

  float speed = 0.02f;

  if (abs(targetX) - abs(posX) > 0) // há diferença entre o alvo e o real
  {
    if (targetX > posX)
      posX += speed;
    else
      posX -= speed;
  }
  else
    posX = targetX;

  if (abs(targetZ) - abs(posZ) > 0) // há diferença entre o alvo e o real
  {
    if (targetZ > posZ)
      posZ += speed;
    else
      posZ -= speed;
  }
  else
    posZ = targetZ;

  gluLookAt(posX, posY, posZ, toX, toY, toZ, 0.f, 1.f, 0.f);
}


void PlayState::MouseFunc(GameEngine*, int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
  {
    x_ini = x;
    y_ini = y;
    obsX_ini = obsX;
    obsY_ini = obsY;
    obsZ_ini = obsZ;
    rotX_ini = rotX;
    rotY_ini = rotY;
    bot = button;
  }
  else bot = -1;
}

void PlayState::MotionFunc(GameEngine*, int x, int y)
{
  if (bot == GLUT_LEFT_BUTTON)
  {
    int deltax = x_ini - x;
    int deltay = y_ini - y;
    rotY = rotY_ini - deltax / SENS_ROT;
    rotX = rotX_ini - deltay / SENS_ROT;
  }

  else if (bot == GLUT_RIGHT_BUTTON)
  {

    int deltaz = y_ini - y;
    obsZ = obsZ_ini + deltaz / SENS_OBS;

  }

  else if (bot == GLUT_MIDDLE_BUTTON)
  {
    int deltax = x_ini - x;
    int deltay = y_ini - y;
    obsX = obsX_ini + deltax / SENS_TRANSL;
    obsY = obsY_ini - deltay / SENS_TRANSL;
  }

  SetObserverPosition();
  glutPostRedisplay();
}

void PlayState::SetLights()
{
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_LIGHT0);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}