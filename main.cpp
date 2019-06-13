#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include "mainwindow.h"

int main(int argc, char *argv[])
{



    QApplication app(argc, argv);

    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette p;
    p = app.palette();
    p.setColor(QPalette::Window, QColor(53,53,53));
    p.setColor(QPalette::Button, QColor(53,53,53));
    p.setColor(QPalette::WindowText, QColor(255,255,255));
    p.setColor(QPalette::Highlight, QColor(142,45,197));
    p.setColor(QPalette::ButtonText, QColor(255,255,255));
    app.setPalette(p);


    MainWindow w;
    w.show();
    
    return app.exec();
}
