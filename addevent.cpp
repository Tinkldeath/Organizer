#include "addevent.h"
#include "ui_addevent.h"

AddEvent::AddEvent(QWidget *parent, IPublisher* publisher, QListWidget * list, QTimer* timer) :
    QDialog(parent),
    ui(new Ui::AddEvent)
{
    pub = publisher;
    widget = list;
    setWindowFlag(Qt::Tool);
    ui->setupUi(this);
    this->t = timer;
    message = new QMessageBox();
    QDate d = QDate::currentDate();
    ui->calendarWidget->setSelectedDate(d);
    QTime t = QTime::currentTime();
    ui->timeEdit->setTime(t);
}

AddEvent::~AddEvent()
{
    delete ui;
    delete message;
}

void AddEvent::on_cancelButton_clicked()
{
    this->close();
}

void AddEvent::on_addEventButton_clicked()
{
    this->t->stop();
    if(ui->lineEventHeader->text() == ""){
        message->setText("Header is necessary field!");
        message->exec();
        return;
    }
    QDate date = ui->calendarWidget->selectedDate();
    QTime time = ui->timeEdit->time();
    QString header = ui->lineEventHeader->text();
    QString frequency = ui->comboNotifications->currentText();
    QString notes = ui->plainTextEdit->toPlainText();
    if(ui->comboMode->currentText() == "Push"){
        PushEventPhabric ph;
        IEvent* newEvent = ph.CreateEvent(date,time,header,frequency,notes);
        pub->AddSubscriber(newEvent);
    }
    else if(ui->comboMode->currentText() == "Dialog"){
        DialogEventPhabric ph;
        IEvent* newEvent = ph.CreateEvent(date,time,header,frequency,notes);
        pub->AddSubscriber(newEvent);
    }
    else{
        SpamEventPhabric ph;
        IEvent* newEvent = ph.CreateEvent(date,time,header,frequency,notes);
        pub->AddSubscriber(newEvent);
    }
    widget->clear();
    message->setText("Event created");
    message->exec();
    pub->Display(widget);
    this->t->start();
    close();
}

