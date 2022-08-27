#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QByteArray>
#include <QTcpSocket>
#include <QVector>
#include <QImage>
#include <QHostAddress>
#include <QTime>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    Server();
    QTcpSocket *socket;
    void sendToUser(QString str);
    QVector<QTcpSocket*> mSockets;
    QByteArray data;
    QString name = "Server";
    void takeImage();


signals:

public slots:
    void incomingConnection(qintptr socketDescriptor);
    void slotReadyRead();

};

#endif // SERVER_H
