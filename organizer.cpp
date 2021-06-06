#include "organizer.h"
#include "ui_organizer.h"
#include <QDebug>

Organizer::Organizer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Organizer)
{
    setWindowFlags(Qt::Window
                   | Qt::WindowTitleHint
                   | Qt::WindowMinimizeButtonHint
                   | Qt::CustomizeWindowHint);
    ui->setupUi(this);
    message = new QMessageBox();
    selectedEvent = nullptr;
    countdownEvent = nullptr;
    publisher = new EventPublisher();
    Parse();
    publisher->Display(ui->listWidget);
    timer = new QTimer();
    timer->setInterval(30000);
    connect(timer,SIGNAL(timeout()),this,SLOT(CheckEvent()));
    timer->start();
    editEvent = new EditEvent(this,ui->listWidget,publisher);
}

Organizer::~Organizer()
{
    timer->stop();
    publisher->Delete();
    delete ui;
    delete message;
    delete editEvent;
    delete timer;
}

void Organizer::Parse(){
    QFile file("storage.txt");
    if(file.open(QIODevice::ReadOnly)){
        QString str = file.readAll();
        QStringList list = str.split("\n");
        QDate d;
        QTime t;
        QString h;
        QString f;
        QString n;
        QString type;
        int nn = list.length();
        for(int i = 0; i < nn; i++){
            QStringList tmp = list[i].split(": ");
            if(tmp[0] == "Type"){
                type = tmp[1];
                continue;
            }
            else if(tmp[0] == "Date"){
                d = QDate::fromString(tmp[1],"dd.MM.yyyy");
                continue;
            }
            else if(tmp[0] == "Time"){
                t = QTime::fromString(tmp[1],"hh:mm");
                continue;
            }
            else if(tmp[0] == "Header"){
                h = tmp[1];
                continue;
            }
            else if(tmp[0] == "Frequency"){
                f = tmp[1];
                continue;
            }
            else if(tmp[0] == "Notes"){
                n = tmp[1];
            }
            else if(tmp[0] == ""){
                continue;
            }
            if(type == "Push"){
                PushEventPhabric ph;
                IEvent* event = ph.CreateEvent(d,t,h,f,n);
                publisher->AddSubscriber(event);
            }
            else if(type == "Dialog"){
                DialogEventPhabric ph;
                IEvent* event = ph.CreateEvent(d,t,h,f,n);
                publisher->AddSubscriber(event);
            }
            else{
                SpamEventPhabric ph;
                IEvent* event = ph.CreateEvent(d,t,h,f,n);
                publisher->AddSubscriber(event);
            }
        }
    }
    else{
        return;
    }
}

void Organizer::Save(){
    QFile file("storage.txt");
    if(file.open(QIODevice::WriteOnly)){
        file.write("");
        file.close();
        file.open(QIODevice::WriteOnly);
        Node<IEvent>* p = publisher->GetSubscribers();
        QString out = "";
        while(p){
            p->key->Print(out);
            p = p->next;
        }
        file.write("");
        std::string str = out.toStdString();
        const char* arr = str.c_str();
        QFile log("events.log");
        if(log.open(QIODevice::WriteOnly)){
            log.write(arr);
        }
        file.write(arr);
        file.close();
    }
}

void Organizer::CheckEvent(){
    QTime t = QTime::currentTime();
    QDate d = QDate::currentDate();
    publisher->NotifySubscrivers(d,t);
    publisher->CheckExecuted();
    ui->listWidget->clear();
    publisher->Display(ui->listWidget);
}

void Organizer::select_event(const QModelIndex &ind)
{
    if(!ind.isValid()){
        return;
    }
    QString header = ind.data(Qt::DisplayRole).value<QString>();
    IEvent* ev = publisher->FindSubscriber(header);
    if(ev == nullptr){
        return;
    }
    selectedEvent = ev;
    ui->lineSelecetedEventTime->setText(ev->GetTime().toString("hh:mm"));
    ui->lineSelectedEventDate->setText(ev->GetDate().toString("dd.MM.yyyy"));
    ui->lineSelectedEventFrequency->setText(ev->GetFrequency());
    ui->lineSelectedEventHeader->setText(ev->GetHeader());
    ui->lineSelectedEventNotes->setText(ev->GetNotes());
}

void Organizer::on_addEventButton_clicked()
{
    AddEvent* addEvent = new AddEvent(this,publisher,ui->listWidget,timer);
    addEvent->show();
}

void Organizer::on_listWidget_clicked(const QModelIndex &index){
    select_event(index);
}

void Organizer::on_saveAndExitButton_clicked()
{
    Save();
    exit(0);
}

void Organizer::on_changeEventButton_clicked()
{
    if(selectedEvent == nullptr){
        message->setText("Choose event or create it first");
        message->exec();
        return;
    }
    editEvent->SetEvent(selectedEvent);
}

void Organizer::on_deleteEventButton_clicked()
{
    if(selectedEvent == nullptr){
        message->setText("Select event first");
        message->exec();
        return;
    }
    ui->listWidget->clear();
    publisher->RemoveSubscriber(selectedEvent);
    publisher->Display(ui->listWidget);
    message->setText("Event deleted");
    message->exec();
}

void Organizer::on_radioDisableAllButton_clicked()
{
    publisher->MuteSubscribers();
    message->setText("All notifications are muted, turn on to enable");
    message->exec();
}

void Organizer::on_radioEnableAllButton_clicked()
{
    publisher->UnmuteSubscribers();
    message->setText("Notifications unmuted");
    message->exec();
}

void Organizer::on_startCountButton_clicked()
{
    if(countdownEvent == nullptr){
        QString n = ui->lineCountdown->text();
        QTime t = ui->countdownEdit->time();
        QTime time(QTime::currentTime().hour() + t.hour(), QTime::currentTime().minute() + t.minute());
        CountDownEventPhabric ph;
        IEvent* countdown = ph.CreateEvent(QDate::currentDate(),time,"Countdown","One time",n);
        publisher->AddSubscriber(countdown);
        ui->listWidget->clear();
        publisher->Display(ui->listWidget);
        countdownEvent = countdown;
        message->setText("Countdown event added");
        message->exec();
    }
    else{
        message->setText("Countdown event is already running, clear or wait first");
        message->exec();
    }
}

void Organizer::on_stopCountButton_clicked()
{
    ui->lineCountdown->clear();
    ui->countdownEdit->setTime(QTime(0,0));
    publisher->RemoveSubscriber(countdownEvent);
    countdownEvent = nullptr;
    message->setText("Countdown event deleted");
    message->exec();
}

void Organizer::on_aboutButton_clicked()
{
    message->setText("About:\n\nOrganizer is a program which produces your own events.\nThere are 4 types of notifications:\n\n1.Push notification creates a popup dialog which will close automatically since 10 seconds.\n\n2.Dialog notification creates a dialog widnow which you have to close manually.\n\n3.Spam event creates many spam notifications whose will fill the entire screen.\n\n4.Countdown notification works like a timer, you can add only one countdown");
    message->exec();
}
