
// MyGLWidget.cpp

#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>
#include <iostream>
#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

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


MyGLWidget::~MyGLWidget() {}

void MyGLWidget::carregaShaders(){
    LL4GLWidget::carregaShaders();
    colFocus1Loc = glGetUniformLocation (program->programId(), "colFocus1");
    posFocus1Loc = glGetUniformLocation (program->programId(), "posFocus1");
    
    colFocus2Loc = glGetUniformLocation (program->programId(), "colFocus2");
    posFocus2Loc = glGetUniformLocation (program->programId(), "posFocus2");
    
    colFocus3Loc = glGetUniformLocation (program->programId(), "colFocus3");
    posFocus3Loc = glGetUniformLocation (program->programId(), "posFocus3");
    
    actLoc = glGetUniformLocation (program->programId(), "activado");
}


void MyGLWidget::initializeGL ()
{
  eixX = glm::vec3(1, 0, 0);
  eixY = glm::vec3(0, 1, 0);


  // Cal inicialitzar l'ús de les funcions d'OpenGL
  initializeOpenGLFunctions();
  glEnable(GL_DEPTH_TEST);

  glClearColor(0.5, 0.7, 1.0, 1.0); // defineix color de fons (d'esborrat)
  carregaShaders();
  tres_focus = false;
  act = 0;
  glUniform1i(actLoc, act);

  iniEscena();
  iniCamera();

  posFocus1 = glm::vec3(-3.5, 10.0, -3.5);
  posFocus2 = glm::vec3(3.5, 10.0, -3.5);
  posFocus3 = glm::vec3(3.5, 10.0, 3.5);

  colFocus1 = glm::vec3(0.9, 0.2, 0.2);
  colFocus2 = glm::vec3(0.0, 1.0, 0.0);
  colFocus3 = glm::vec3(0.2, 0.2, 0.9);
/*
  glm::vec3 aux = glm::vec3((View * glm::vec4(posFocus1, 1.0f)));
  glUniform3fv(posFocus1Loc, 1, &aux[0]);
  glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);

  aux = glm::vec3((View * glm::vec4(posFocus2, 1.0f)));
  glUniform3fv(posFocus2Loc, 1, &aux[0]);
  glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);

  aux = glm::vec3((View * glm::vec4(posFocus3, 1.0f)));
  glUniform3fv(posFocus3Loc, 1, &aux[0]);
  glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);
  */
  glUniform3fv(posFocus1Loc, 1, &posFocus1[0]);
  glUniform3fv(colFocus1Loc, 1, &colFocus1[0]);

  glUniform3fv(posFocus2Loc, 1, &posFocus2[0]);
  glUniform3fv(colFocus2Loc, 1, &colFocus2[0]);

  glUniform3fv(posFocus3Loc, 1, &posFocus3[0]);
  glUniform3fv(colFocus3Loc, 1, &colFocus3[0]);

}


void MyGLWidget::keyPressEvent(QKeyEvent *e) {
    makeCurrent();
    switch (e->key()) {
        // no modifiqueu el següent comportament:
        case Qt::Key_Left:
            angleCotxe -= float((M_PI)/4);
            break;
        case Qt::Key_Right:
            angleCotxe += float((M_PI)/4);
            break;
        case Qt::Key_F:
            tres_focus = !tres_focus;
            if(tres_focus)
            {
              act = 1;
              glUniform1i(actLoc, act);
            }
            else
            {
                act = 0;
                glUniform1i(actLoc, act);
            }
            break;
        case Qt::Key_R:
            initializeGL();
            break;
        default:
            LL4GLWidget::keyPressEvent(e);
    }
    update();
}

void MyGLWidget::clicEsq()
{
  makeCurrent();
  angleCotxe -= float((M_PI)/4);
  update ();
}

void MyGLWidget::clicDrt()
{
  makeCurrent();
  angleCotxe += float((M_PI)/4);
  update ();
}
