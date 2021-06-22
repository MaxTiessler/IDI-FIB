#include "MyLCDNumber.h"

MyLCDNumber::MyLCDNumber(QWidget *parent)
    :QLCDNumber(parent)
{
// Inicialització d'atributs si cal
    setOctMode();
}


// implementacio slots
void MyLCDNumber::incrementa()
{
    int valor_act = intValue();
    valor_act++;
    if(valor_act == 64) valor_act = 0;
    display(valor_act);
}

void MyLCDNumber::reset()
{
    display(0);
}

