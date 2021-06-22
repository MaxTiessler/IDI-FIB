#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ( );

    // keyPressEvent - Es cridat quan es prem una tecla
    virtual void keyPressEvent (QKeyEvent *event);
    // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ( );
    virtual void iniCamera ( );
    virtual void iniEscena ();
    virtual void homerTransform (int i, int j);
    void drawTauler();
    bool notoutofTauler(int i, int j);
    //virtual void projectTransform();

    int deltai[8] = {-1, -2, -2, -1,  1,  2,  2,  1};
    int deltaj[8] = {-2, -1,  1,  2,  2,  1, -1, -2};
    int   xH, zH;
    float angleH;
  private:
    int printOglError(const char file[], int line, const char func[]);

};
