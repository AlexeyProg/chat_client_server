#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkProxy>
#include <QImage>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_send->setEnabled(false);
    ui->lineEdit_message->setEnabled(false);

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_connect_clicked()
{
    socket->connectToHost("127.0.0.1",1222);
    if(socket->waitForConnected(5000))
    {
        QString connected = "*CONNECTED*";
        qDebug() << connected << socket->state();
        ui->textBrowser_main->append(connected + "\n" + "**********" + "\n");
        ui->pushButton_send->setEnabled(true);
        ui->lineEdit_message->setEnabled(true);
        ui->lineEdit_message->clear();
    }
    else
    {
        qDebug() << "**Not connected**";
        qDebug() << socket->errorString();
        qDebug() << socket->state();
    }
}

void MainWindow::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_8);
    if(in.status() == QDataStream::Ok)
    {
        qDebug() << "Datastream ok  waiting image";
        bool flag;
        QImage img ;
        in >> img >> flag;
        qDebug() << "flag is " << flag;
        QPixmap pix = QPixmap::fromImage(img);
        ui->label->setPixmap(pix);
    }
}

void MainWindow::sendToServer(QString path)
{
    /*
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    QString user = QTime::currentTime().toString() + " USER" +  ":" + str;
    out << user;
    socket->write(data);
    ui->lineEdit_message->clear();*/

    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    QImage img(path);
    bool flag = true;
    out << img << flag;
    socket->write(data);
    ui->lineEdit_message->clear();
}

void MainWindow::on_pushButton_send_clicked()
{
    sendToServer(ui->lineEdit_message->text());
}

void MainWindow::on_lineEdit_message_returnPressed() //отправка сообщения по нажатию на "Enter"
{
    sendToServer(ui->lineEdit_message->text());
}
