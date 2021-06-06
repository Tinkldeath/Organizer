#include "notification.h"
#include "ui_notification.h"

notification::notification(QWidget *parent, QString header, QString notes) :
    QWidget(parent),
    ui(new Ui::notification)
{
    ui->setupUi(this);
    ui->label->setText(header);
    ui->plainTextEdit->setPlainText(notes);
    setWindowFlags(  Qt::CustomizeWindowHint
                   | Qt::WindowCloseButtonHint
                   | Qt::Dialog
                   | Qt::WindowStaysOnTopHint
                   );
}

notification::~notification()
{
    delete ui;
}
