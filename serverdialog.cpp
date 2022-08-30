#include "serverdialog.h"
#include "ui_serverdialog.h"
#include <QTime>

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Server's dialog");

}

void ServerDialog::takeImage(QImage img,bool flag)
{
    if(flag)
    {
        QString str = QTime::currentTime().toString() + ": Client correctrly sent the image";
        ui->textBrowser->append(str);
        ui->label->setPixmap(QPixmap::fromImage(img));
    }
    else
    {
        QString str = QTime::currentTime().toString() + ": The image was sent incorrectly";
        ui->textBrowser->append(str);
    }
}

ServerDialog::~ServerDialog()
{
    delete ui;
}
