#include "push.h"
#include "ui_push.h"

Push::Push(QWidget *parent, QString header, QString notes, int x, int y) :
    QWidget(parent),
    ui(new Ui::Push)
{
    ui->setupUi(this);
    ui->labelHeader->setText(header);
    ui->labelNotes->setText(notes);
    setWindowFlags(/*Qt::FramelessWindowHint |*/
                   Qt::WindowStaysOnTopHint |
                   Qt::WindowTitleHint |
                   Qt::CustomizeWindowHint);
    setGeometry(x,y,300,100);
    timer = new QTimer();
    timer->start(10000);
    connect(timer,SIGNAL(timeout()),this,SLOT(close()));
}

Push::~Push()
{
    delete timer;
    delete ui;
}

void Push::on_closeButton_clicked()
{
    this->close();
}

