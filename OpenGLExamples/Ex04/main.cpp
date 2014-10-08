#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>

GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ = 200, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 44;
int x_ini, y_ini, bot;

float X[4] = { -100, -30, -65, 65 };
float Y[4] = { 0, 15, 50, 50 };
float Z[4] = { -100, 0, 0, 0 };
float delta = 0.4;
int index = 0;

#define SENS_ROT	5.0
#define SENS_OBS	10.0
#define SENS_TRANSL	30.0

void PosicionaObservador(void)
{

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glTranslatef(-obsX, -obsY, -obsZ);
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);
  gluLookAt(0.0, 40.0, 200.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void drawPlane()//Desenha o plano
{
  glBegin(GL_POLYGON);
  glVertex3f(1, 0, 1);
  glVertex3f(1, 0, 0);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, 1);
  glEnd();
}


void Objetos(void)
{
  // DRAW PLANE
  glPushMatrix();
  glColor3f(0, 1, 0);
  glTranslatef(X[0], Y[0], Z[0]);
  glScalef(200, 200, 200);
  drawPlane();
  glPopMatrix();

  // DRAW SPHERE
  glPushMatrix();
  glColor3f(1, 1, 0);
  glTranslated(X[1], Y[1], Z[1]);
  glutSolidSphere(30, 16, 16);
  glPopMatrix();

  // DRAW WALLS
  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslated(X[2], Y[2], Z[2]);
  glScalef(0.2, 3.0, 1.0);
  glutSolidCube(35);
  glPopMatrix();

  glPushMatrix();
  glColor3f(1, 0, 0);
  glTranslated(X[3], Y[3], Z[3]);
  glScalef(0.2, 3.0, 1.0);
  glutSolidCube(35);
  glPopMatrix();
  glutSwapBuffers();
}

void EspecificaParametrosVisualizacao(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(angle, fAspect, 0.5, 500);
  PosicionaObservador();
}

void Desenha(void)
{

  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  EspecificaParametrosVisualizacao();
  Objetos();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  // Para previnir uma divis�o por zero
  if (h == 0) h = 1;

  // Especifica as dimens�es da viewport
  glViewport(0, 0, w, h);

  // Calcula a corre��o de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  EspecificaParametrosVisualizacao();
}

void Teclado(unsigned char key, int x, int y)
{
  printf("%d\n", key);
  if (key == 27)
    exit(0);

}

void GerenciaMouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN)
  {
    // Salva os par�metros atuais
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
void GerenciaMovim(int x, int y)
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
  PosicionaObservador();
  glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y)
{
  if (key == GLUT_KEY_F1)
  {
    index++;
    index %= 4;
  }
  if (key == GLUT_KEY_LEFT)
  {
    X[index] -= 4;
  }
  if (key == GLUT_KEY_RIGHT)
  {
    X[index] += 4;
  }
  if (key == GLUT_KEY_UP)
  {
    Z[index] += 4;
  }
  if (key == GLUT_KEY_DOWN)
  {
    Z[index] -= 4;
  }
  if (key == GLUT_KEY_HOME)
  {
    Y[index] += 4;
  }
  if (key == GLUT_KEY_END)
  {
    Y[index] -= 4;
  }
  glutPostRedisplay();
}

void TimerFunction(int value)
{
  if (X[1] < -30) delta = 0.4;    //Atualiza os valores da vari�vel X
  if (X[1] > 30) delta = -0.4;
  X[1] += delta;
  glutPostRedisplay();          //Atualiza a tela
  glutTimerFunc(33, TimerFunction, 1); //Faz a nova chamada para a fun��o;
}

int main(void)
{
  int argc = 0;
  char *argv[] = { (char *)"gl", 0 };
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(5, 5);
  glutInitWindowSize(450, 450);
  glutCreateWindow("Movimenta��o 3D");
  glutTimerFunc(33, TimerFunction, 1); // 33 ms
  glutDisplayFunc(Desenha);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutKeyboardFunc(Teclado);
  glutSpecialFunc(TeclasEspeciais);
  glutMotionFunc(GerenciaMovim);
  glutMouseFunc(GerenciaMouse);
  glutMainLoop();

  return 0;
}