#ifndef SERVER1_H
#define SERVER1_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QImage>
#include <serverdialog.h>

class Server1 : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server1(QObject *parent = nullptr);

    QTcpSocket *socket;

    void incomingConnection(qintptr socketDescriptor);
    ServerDialog dial;
public slots:
    void slotReadyRead();
};

#endif // SERVER1_H
