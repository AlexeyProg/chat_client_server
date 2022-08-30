#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>
#include <QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *socket;
    QByteArray data;

public slots:
    void connectServer();
    void sendToServer();

private slots:
    void on_lineEdit_message_returnPressed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
