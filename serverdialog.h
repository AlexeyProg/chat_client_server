#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QImage>
#include <QPixmap>

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = nullptr);
    ~ServerDialog();
    void takeImage(QImage img,bool flag);

private:
    Ui::ServerDialog *ui;
};

#endif // SERVERDIALOG_H
