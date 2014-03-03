#include <QtGui/QApplication>
#include "FOgreWidget.h"
#include <QVBoxLayout>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget widget ;
    widget.setGeometry (10,10,640,480) ;
    FOgreWidget ogreWidget(&widget,QString("robot")) ;
    ogreWidget.setGeometry (10,10,640,480) ;
    ogreWidget.Initialize() ;
    widget.show() ;

    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
