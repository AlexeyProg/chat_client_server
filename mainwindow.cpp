#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Client's dialog");
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(disconnected()),this,SLOT(deleteLater()));
    connect(ui->pushButton_connect,SIGNAL(clicked()),SLOT(connectServer()));
    connect(ui->pushButton_send,SIGNAL(clicked()),SLOT(sendToServer()));

    ui->lineEdit_message->setEnabled(false);
    ui->pushButton_send->setEnabled(false);
}

void MainWindow::connectServer()
{
    socket->connectToHost("localhost",12);
    if(socket->waitForConnected(5000))
    {
        QString con = "***CONNECTED***";
        ui->textBrowser_main->append(con);
        ui->pushButton_connect->setEnabled(false);
        ui->pushButton_send->setEnabled(true);
        ui->lineEdit_message->setEnabled(true);
        ui->lineEdit_message->clear();
    }
    else
    {
        QString str = "***Not connected***";
        ui->textBrowser_main->append(str);
        qDebug() << socket->errorString() << socket->state();
    }
}

void MainWindow::sendToServer()
{
    data.clear();
    bool flag = true;
    QImage img(ui->lineEdit_message->text());
    if(img.isNull())
    {
        QString str = QTime::currentTime().toString() + ": The image is invalid";
        ui->textBrowser_main->append(str);
        flag = false;
    }
    else
    {
        QString str = QTime::currentTime().toString() + ": The image was sent";
        ui->textBrowser_main->append(str);
    }
    QDataStream out(&data,QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_6_0);
    out << img << flag;
    socket->write(data);
    ui->lineEdit_message->clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_message_returnPressed()
{
    sendToServer();
}

