#include "mainwindow.h"
#include <server1.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Server1 s;
    w.show();
    return a.exec();
}
