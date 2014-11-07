#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>

#define SENS_ROT	10.0
#define SENS_OBS	1.0
#define SENS_TRANSL	1.0

#define LIGHT_COUNT 2
#define GL_LIGHT(X) GL_LIGHT##X

#define TAM 1000
#define D 100

bool isGouraudRender = true;
int currentLight = 0;
int x_ini, y_ini, bot;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY = 200, obsZ = 400, obsX_ini, obsY_ini, obsZ_ini;
GLfloat fAspect = 1, angle = 45;

GLfloat luzAmbiente[2][4] = { { 0.2, 0.2, 0.2, 1.0 }, { 0.2, 0.2, 0.2, 1.0 } };
GLfloat luzDifusa[2][4] = { { 0.7, 0.7, 0.7, 1.0 }, { 0.7, 0.7, 0.7, 1.0 } };		 // "cor"
GLfloat luzEspecular[2][4] = { { 1.0, 1.0, 1.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 } }; // "brilho"
GLfloat posicaoLuz[2][4] = { { 0.0, 30.0, 120.0, 1.0 }, { 0.0, -30.0, 120.0, 1.0 } };
GLfloat corLuz[2][3] = { { 1.f, 1.f, 0.f }, { 1.f, 0.f, 0.f } };

void PosicionaObservador(void)
{
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  //glTranslatef(-obsX,-obsY,-obsZ); //Outra opcao de camera
  glRotatef(rotX, 1, 0, 0);
  glRotatef(rotY, 0, 1, 0);

  gluLookAt(obsX, obsY, obsZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
  // Especifica sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de projeção
  glLoadIdentity();

  // Especifica a projeção perspectiva
  gluPerspective(angle, fAspect, 0.4, 5000);

  // Especifica posição do observador e do alvo
  PosicionaObservador();
}

void DesenhaChao()
{
  //Flags para determinar a cord de cada quadrado
  bool flagx, flagz;
  //Define a normal apontando para cima
  glNormal3f(0, 1, 0);

  glBegin(GL_QUADS);
  flagx = false;
  //X varia de -TAM a TAM, de D em D
  for (float x = -TAM; x<TAM; x += D)
  {
    //Flagx determina a cor inicial
    if (flagx) flagz = false;
    else flagz = true;
    //Z varia de -TAM a TAM, de D em D
    for (float z = -TAM; z<TAM; z += D)
    {
      //Escolhe cor
      if (flagz)
        glColor3f(0.4, 0.4, 0.4);
      else
        glColor3f(1, 1, 1);
      //E desenha o quadrado
      glVertex3f(x, -60, z);
      glVertex3f(x + D, -60, z);
      glVertex3f(x + D, -60, z + D);
      glVertex3f(x, -60, z + D);
      //Alterna cor
      flagz = !flagz;
    }
    //A cada coluna, alterna cor inicial
    flagx = !flagx;
  }
  glEnd();
}

void DefineIluminacao()
{
  // Capacidade de brilho do material
  GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
  GLint especMaterial = 60;

  // Habilita o modelo de colorização de Gouraud ou Flat
  if (isGouraudRender)
    glShadeModel(GL_SMOOTH);
  else
    glShadeModel(GL_FLAT);

  // Define a refletância do material
  glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
  // Define a concentração do brilho
  glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

  // Ativa o uso da luz ambiente
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente[0]);

  unsigned short lights[LIGHT_COUNT] = { GL_LIGHT0, GL_LIGHT1 };

  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    // Define os parâmetros da luz de número 0
    glLightfv(lights[i], GL_AMBIENT, luzAmbiente[i]);
    glLightfv(lights[i], GL_DIFFUSE, luzDifusa[i]);
    glLightfv(lights[i], GL_SPECULAR, luzEspecular[i]);
    glLightfv(lights[i], GL_POSITION, posicaoLuz[i]);
  }

  //Desabilita iluminacao para desenhar a esfera
  glDisable(GL_LIGHTING);
  //Desenha esfera na posição da fonte de luz
  glPushMatrix();
  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    glTranslatef(posicaoLuz[i][0], posicaoLuz[i][1], posicaoLuz[i][2]);
    glColor3f(corLuz[i][0], corLuz[i][1], corLuz[i][2]);
    glutSolidSphere(5, 50, 50);
  }
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

// Função callback chamada para fazer o desenho
void Desenha(void)
{
  // Limpa a janela e o depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  EspecificaParametrosVisualizacao();
  DesenhaChao();

  DefineIluminacao();

  glColor3f(0.0f, 0.0f, 1.0f);

  // Desenha o teapot com a cor corrente (solid)
  glutSolidTeapot(50.0f);

  glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
  // Especifica que a cor de fundo da janela será preta
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  DefineIluminacao();

  // Habilita a definição da cor do material a partir da cor corrente
  glEnable(GL_COLOR_MATERIAL);
  //Habilita o uso de iluminação
  glEnable(GL_LIGHTING);
  // Habilita a luz de número 0
  glEnable(GL_LIGHT0);
  // Habilita a luz de número 0
  glEnable(GL_LIGHT1);
  // Habilita o depth-buffering
  glEnable(GL_DEPTH_TEST);
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  // Para previnir uma divisão por zero
  if (h == 0) h = 1;

  // Especifica o tamanho da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  EspecificaParametrosVisualizacao();
}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
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

void GerenciaTeclado(unsigned char key, int, int)
{
  if (key == 27) exit(0);

  switch (key)
  {
  case 'q':
    luzAmbiente[currentLight][0] -= 0.1;
    luzAmbiente[currentLight][1] -= 0.1;
    luzAmbiente[currentLight][2] -= 0.1;
    break;
  case 'w':
    luzAmbiente[currentLight][0] += 0.1;
    luzAmbiente[currentLight][1] += 0.1;
    luzAmbiente[currentLight][2] += 0.1;
    break;
  case 'a':
    luzDifusa[currentLight][0] -= 0.1;
    luzDifusa[currentLight][1] -= 0.1;
    luzDifusa[currentLight][2] -= 0.1;
    break;
  case 's':
    luzDifusa[currentLight][0] += 0.1;
    luzDifusa[currentLight][1] += 0.1;
    luzDifusa[currentLight][2] += 0.1;
    break;
  case 'z':
    luzEspecular[currentLight][0] -= 0.1;
    luzEspecular[currentLight][1] -= 0.1;
    luzEspecular[currentLight][2] -= 0.1;
    break;
  case 'x':
    luzEspecular[currentLight][0] += 0.1;
    luzEspecular[currentLight][1] += 0.1;
    luzEspecular[currentLight][2] += 0.1;
    break;
  }

  glutPostRedisplay();
}

void GerenciaTecladoEspecial(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_LEFT:
    posicaoLuz[currentLight][0] -= 2;
    break;
  case GLUT_KEY_RIGHT:
    posicaoLuz[currentLight][0] += 2;
    break;
  case GLUT_KEY_UP:
    posicaoLuz[currentLight][1] += 2;
    break;
  case GLUT_KEY_DOWN:
    posicaoLuz[currentLight][1] -= 2;
    break;
  case GLUT_KEY_PAGE_UP:
    posicaoLuz[currentLight][2] -= 2;
    break;
  case GLUT_KEY_PAGE_DOWN:
    posicaoLuz[currentLight][2] += 2;
    break;
  case GLUT_KEY_F10:
    isGouraudRender = !isGouraudRender;
    break;
  case GLUT_KEY_F1:
    currentLight++;
    currentLight %= LIGHT_COUNT;
    break;
  }

  glutPostRedisplay();
}

// Programa Principal
int main(void)
{
  int argc = 0;
  char *argv[] = { (char *)"gl", 0 };

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(800, 600);
  glutCreateWindow("Exercicio de Iluminacao");
  glutDisplayFunc(Desenha);
  glutReshapeFunc(AlteraTamanhoJanela);
  glutMotionFunc(GerenciaMovim);
  glutMouseFunc(GerenciaMouse);
  glutKeyboardFunc(GerenciaTeclado);
  glutSpecialFunc(GerenciaTecladoEspecial);
  Inicializa();
  glutMainLoop();

  return 0;
}
