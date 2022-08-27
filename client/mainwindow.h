#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define IMAGE_PATH "/Users/sokol/Desktop/qt_projects/chat_task/application-exit.png"


#include <QMainWindow>
#include <QTcpSocket>
#include <QTime>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTcpSocket *socket;
    QByteArray data;
    void sendToServer(QString path);

private slots:
    void on_pushButton_connect_clicked();
    void slotReadyRead();

    void on_pushButton_send_clicked();

    void on_lineEdit_message_returnPressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
