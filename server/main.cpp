#include <iostream>
#include <server.h>
#include <QCoreApplication>
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
    return a.exec();
}

