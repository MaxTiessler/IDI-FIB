#include <QLabel>
class MyLabel: public QLabel
{
	Q_OBJECT
	public:
		MyLabel (QWidget *parent);
		
	public slots:
        void add();
        void reset();
    signals:
        void funciox();
}; 
