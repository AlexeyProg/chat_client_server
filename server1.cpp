#include "server1.h"

Server1::Server1(QObject *parent)
    : QTcpServer{parent}
{
    dial.show();
    if(this->listen(QHostAddress::Any,12))
        qDebug() << "Listening port is " << this->serverPort();
}

void Server1::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);

    connect(socket,SIGNAL(readyRead()),SLOT(slotReadyRead()));
    connect(socket,SIGNAL(disconnected()),SLOT(deleteLater()));
}

void Server1::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    bool flag;
    QImage img;
    QDataStream in(socket);
    if(in.status() == QDataStream::Ok)
    {
        in.setVersion(QDataStream::Qt_6_0);
        in >> img >> flag;
        qDebug() << "flag is " << flag;
        dial.takeImage(img,flag);
    }
}
