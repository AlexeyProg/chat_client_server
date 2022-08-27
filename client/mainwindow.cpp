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
    socket->connectToHost("127.0.0.1",222);
    if(socket->waitForConnected(5000))
    {
        QString connected = "*CONNECTED*";
        qDebug() << connected << socket->state();
        ui->textBrowser_main->append(connected + "\n" + "**********" + "\n");
        ui->pushButton_send->setEnabled(true);
        ui->lineEdit_message->setEnabled(true);
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
        QString str;
        in >> str;
        ui->textBrowser_main->append(str);
    }
    else
        ui->textBrowser_main->append("Data stream error");
}

void MainWindow::sendToServer(QString str)
{
    data.clear();
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_8);
    QString user = QTime::currentTime().toString() + " USER" +  ":" + str;
    out << user;
    socket->write(data);
    ui->lineEdit_message->clear();

//    data.clear();
//    QDataStream out(&data,QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_8);
//    QImage img(IMAGE_PATH);
//    bool flag = true;
//    out << img << flag;
//    socket->write(data);
//    ui->lineEdit_message->clear();

}

void MainWindow::sendImage(QString str)
{

    data.clear();
    QImage img(IMAGE_PATH);
    QByteArray *ba;
    bool flag = 1;
    QDataStream out(&data,QIODevice::ReadOnly);
    out << img << flag;
    socket->write(data);
}

void MainWindow::on_pushButton_send_clicked()
{
    sendToServer(ui->lineEdit_message->text());
//    sendImage("fdf");
}

void MainWindow::on_lineEdit_message_returnPressed() //отправка сообщения по нажатию на "Enter"
{
    sendToServer(ui->lineEdit_message->text());
}
