#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

void MyGLWidget::initializeGL ()
{
  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  creaBuffersEscac();
  creaBuffersHomer();
  iniEscena();
  iniCamera();
}

void MyGLWidget::iniEscena()
{
  angleH     = 0.0;
  xH         = zH  = 0;  // posició x i z final del Homer
}


void MyGLWidget::drawTauler()
{
    for(int i = 0; i < 8; ++i)
    {
        for(int j = 0; j < 8; ++j)
        {
            if((i%2 == 0 and j%2 == 0) or (i%2 == 1 and j%2 == 1))
            {
                escacTransform(i-3, j-3);
                glBindVertexArray (VAO_Escac);
                glUniform1i(indexColorLoc, 3);  // color = 3 -- color escac negre (0.2, 0.2, 0.2)
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray (0);
            }
            else
            {
                escacTransform(i-3, j-3);
                glBindVertexArray (VAO_Escac);
                glUniform1i(indexColorLoc, 1);  // color = 1 -- color escac blanc (0.8, 0.8, 0.8)
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray (0);
            }
        }
    }
}

void MyGLWidget::iniCamera(){

  obs = glm::vec3(0.5, 2, 12);
  vrp = glm::vec3(0.5, 0, 0.5);
  up = glm::vec3(0, 1, 0);
  fov = M_PI/4;
  ra  = 1.0;
  znear =  6;
  zfar  = 16;

  viewTransform();
  projectTransform();
}
void MyGLWidget::paintGL ()
{
  // descomentar per canviar paràmetres
  // glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Homer
  homerTransform(xH, zH);
  glBindVertexArray (VAO_Homer);
  glUniform1i(indexColorLoc, 2);  // color = 2 -- color per vèrtex
  glDrawArrays(GL_TRIANGLES, 0, homer.faces().size()*3);
  glBindVertexArray (0);

  // Escac
  drawTauler();
}
void MyGLWidget::homerTransform (int x, int z)
{
  // Matriu de transformació de Homer
  glm::mat4 TG(1.0f);
  TG = glm::translate(TG, glm::vec3(x, -0.5, z));
  TG = glm::rotate(TG, angleH, glm::vec3(0, 1, 0));
  TG = glm::scale(TG, glm::vec3(escalaH));
  TG = glm::translate(TG, -baseHomer);
  glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}
bool MyGLWidget::notoutofTauler(int i, int j)
{
    return ((i < 4 and i > -4) and (j < 4 and j > -4));
}
void MyGLWidget::keyPressEvent(QKeyEvent* event)
{
  makeCurrent();
  switch (event->key()) {
    default: event->ignore(); break;
    case Qt::Key_1:{
          if(notoutofTauler(xH+deltai[0], zH+deltaj[0]))
          {
            xH = xH + deltai[0];
            zH = zH + deltaj[0];
            float anglegir = angleH - float(M_PI);
            angleH -= anglegir;
            homerTransform(xH, zH);
          }
          break;
        }
    case Qt::Key_2:{
        if(notoutofTauler(xH+deltai[1], zH+deltaj[1]))
        {
         xH = xH + deltai[1];
         zH = zH + deltaj[1];
         homerTransform(xH, zH);
        }
        break;
      }
    case Qt::Key_3:{
      if(notoutofTauler(xH+deltai[2], zH+deltaj[2]))
      {
       xH = xH + deltai[2];
       zH = zH + deltaj[2];
      }
      break;
    }
    case Qt::Key_4:{
      if(notoutofTauler(xH+deltai[3], zH+deltaj[3]))
      {
       xH = xH + deltai[3];
       zH = zH + deltaj[3];
      }
      break;
    }
    case Qt::Key_5:{
      if(notoutofTauler(xH+deltai[4], zH+deltaj[4]))
      {
       xH = xH + deltai[4];
       zH = zH + deltaj[4];
      }
      break;
    }
    case Qt::Key_6:{
      if(notoutofTauler(xH+deltai[5], zH+deltaj[5]))
      {
       xH = xH + deltai[5];
       zH = zH + deltaj[5];
      }
      break;
    }
  case Qt::Key_7:{
      if(notoutofTauler(xH+deltai[6], zH+deltaj[6]))
      {
       xH = xH + deltai[6];
       zH = zH + deltaj[6];
      }
      break;
    }
  case Qt::Key_8:{
      if(notoutofTauler(xH+deltai[7], zH+deltaj[7]))
      {
       xH = xH + deltai[7];
       zH = zH + deltaj[7];
      }
      break;
    }
    }
    update();
}

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget()
{

}
