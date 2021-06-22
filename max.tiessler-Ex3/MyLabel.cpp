#include "MyLabel.h"
MyLabel::MyLabel(QWidget *parent) 
	:QLabel(parent) {
    QFont f( "Arial", 30, QFont::Bold);
    setFont(f);
    setStyleSheet("background-color: green");
}

// implementacio slots
void MyLabel::add()
{
    QString text_act = text();
    if(text_act == "0")
        setText("1"), setStyleSheet("background-color: yellow");
    else
    {
        setText("0");
        setStyleSheet("background-color: green");
        emit funciox();
    }

} 
void MyLabel::reset()
{
    setText("0");
    setStyleSheet("background-color: green");
}
