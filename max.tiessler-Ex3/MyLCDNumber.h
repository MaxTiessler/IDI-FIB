#include <QLCDNumber>
class MyLCDNumber:public QLCDNumber
{
    Q_OBJECT
    public:
        MyLCDNumber(QWidget *parent);

    public slots:
        void incrementa();
        void reset();
};
