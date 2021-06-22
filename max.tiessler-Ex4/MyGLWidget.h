// MyGLWidget.h
#include "LL4GLWidget.h"

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  private:
    int printOglError(const char file[], int line, const char func[]);
    virtual void keyPressEvent (QKeyEvent *);
    virtual void carregaShaders(); //cargar los uniforms de los nuevos focos
    virtual void initializeGL();

    glm::vec3 colFocus1, posFocus1;
    glm::vec3 colFocus2, posFocus2;
    glm::vec3 colFocus3, posFocus3;
    int vistalocal;
    int act;
    bool tres_focus; //false = 1 focus, true = 3 focus
    //UNIFORMS
    GLuint colFocus1Loc, posFocus1Loc;
    GLuint colFocus2Loc, posFocus2Loc;
    GLuint colFocus3Loc, posFocus3Loc;
    GLuint actLoc; 
    public slots:
      void clicEsq();
      void clicDrt();

};
