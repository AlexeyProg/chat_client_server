#include "server.h"
#include <QDebug>

Server::Server()
{
    if(!this->listen(QHostAddress::Any,1222))
        qDebug() << "Error listening server";
    else
    {
        qDebug() << " Listen port is : "<< this->serverPort();;
    }

}
void Server::incomingConnection(qintptr socketDescriptor)
{
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));

    mSockets.push_back(socket);
    qDebug() << "Socket was added to vector , user descryptor is " << socket->socketDescriptor();

}

void Server::slotReadyRead()
{
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_8);
    if(in.status() == QDataStream::Ok)
    {
        bool flag;
        QImage img;
        in >> img >> flag;
        qDebug() << "bool is " << flag;

        QByteArray newarr;
        newarr.clear();
        QDataStream out1(&newarr,QIODevice::WriteOnly);
        out1.setVersion(QDataStream::Qt_4_8);
        QImage i = img;
        bool newflag = true;
        out1 << i << newflag;
        socket->write(newarr);

    }
    else
    {
        qDebug() << "Datastream error";
    }
}

void Server::sendToUser(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    out << str;
    for(QTcpSocket* item : mSockets)
    {
        item->write(data);
    }
}

void Server::takeImage()
{
    bool flag;
    QByteArray ba;
    QDataStream in(ba);
    QImage i;
    in >> i >> flag;
    if(flag)
    {
        qDebug() << " Good data";
    }
}
