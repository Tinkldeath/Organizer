#include "event.h"


//========================================================================================================== Реализация push-уведомления
PushEvent::PushEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    date = inDate;
    time = inTime;
    header = inHeader;
    frequency = inFrequency;
    notes = inNotes;
    muted = false;
    executed = false;
}

void PushEvent::Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes){
    date = newDate;
    time = newTime;
    header = newHeader;
    frequency = newFrequency;
    notes = newNotes;
}

void PushEvent::Check(QDate inDate, QTime inTime){
    if(date == inDate && time.hour() == inTime.hour() && time.minute() == inTime.minute() && frequency == "One time" && muted == false){
        Show();
        executed = true;
    }
    else if(time.minute() == inTime.minute() && frequency == "Every hour"){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.year() != inDate.year() && muted == false){
        executed = true;
    }
    else return;
}

void PushEvent::Mute(){
    muted = true;
}

void PushEvent::Unmute(){
    muted = false;
}

void PushEvent::Show(){
    Push* event1 = new Push(nullptr,header,notes,0,0);
    event1->show();
}

void PushEvent::Print(QString &out){
    out += "Type: Push\nDate: " + date.toString("dd.MM.yyyy") + "\nTime: " + time.toString("hh:mm") + "\nHeader: " + header + "\nFrequency: "
    + frequency + "\nNotes: " + notes + "\n\n";
}

void PushEvent::Display(QListWidget* widget){
    QVariant v;
    v.setValue(this);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole,header);
    item->setData(Qt::UserRole, v);
    widget->addItem(item);
}

bool PushEvent::Executed(){
    return executed;
}

bool PushEvent::Muted(){
    return muted;
}


//========================================================================================================== Реализация dialog-уведомления

DialogEvent::DialogEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    date = inDate;
    time = inTime;
    header = inHeader;
    frequency = inFrequency;
    notes = inNotes;
    muted = false;
    executed = false;
}

void DialogEvent::Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes){
    date = newDate;
    time = newTime;
    header = newHeader;
    frequency = newFrequency;
    notes = newNotes;
}

void DialogEvent::Check(QDate inDate, QTime inTime){
    if(date == inDate && time.hour() == inTime.hour() && time.minute() == inTime.minute() && frequency == "One time" && muted == false){
        Show();
        executed = true;
    }
    else if(time.minute() == inTime.minute() && frequency == "Every hour"){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.year() != inDate.year() && muted == false){
        executed = true;
    }
    else return;
}

void DialogEvent::Mute(){
    muted = true;
}

void DialogEvent::Unmute(){
    muted = false;
}

void DialogEvent::Show(){
    notification* d = new notification(nullptr,header,notes);
    d->show();
}

void DialogEvent::Print(QString &out){
    out += "Type: Push\nDate: " + date.toString("dd.MM.yyyy") + "\nTime: " + time.toString("hh:mm") + "\nHeader: " + header + "\nFrequency: "
    + frequency + "\nNotes: " + notes + "\n\n";
}

void DialogEvent::Display(QListWidget* widget){
    QVariant v;
    v.setValue(this);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole,header);
    item->setData(Qt::UserRole, v);
    widget->addItem(item);
}

bool DialogEvent::Executed(){
    return executed;
}

bool DialogEvent::Muted(){
    return muted;
}


//========================================================================================================== Реализация spam-уведомления

SpamEvent::SpamEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    date = inDate;
    time = inTime;
    header = inHeader;
    frequency = inFrequency;
    notes = inNotes;
    muted = false;
    executed = false;
}

void SpamEvent::Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes){
    date = newDate;
    time = newTime;
    header = newHeader;
    frequency = newFrequency;
    notes = newNotes;
}

void SpamEvent::Check(QDate inDate, QTime inTime){
    if(date == inDate && time.hour() == inTime.hour() && time.minute() == inTime.minute() && frequency == "One time" && muted == false){
        Show();
        executed = true;
    }
    else if(time.minute() == inTime.minute() && frequency == "Every hour"){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every day" && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every week" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.month() != inDate.month() && muted == false){
        executed = true;
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && muted == false){
        Show();
    }
    else if(frequency == "Every month" && date.day() == inDate.day() && time.hour() == inTime.hour() && time.minute() == inTime.minute() && date.year() != inDate.year() && muted == false){
        executed = true;
    }
    else return;
}

void SpamEvent::Mute(){
    muted = true;
}

void SpamEvent::Unmute(){
    muted = false;
}

void SpamEvent::Show(){
    for(int i = 0; i < 4; i++){
        Push* event1 = new Push(nullptr,header,notes,0,200*i);
        event1->show();
    }
    notification* n = new notification(nullptr,header,notes);
    n->show();
    for(int i = 0; i < 4; i++){
        Push* event1 = new Push(nullptr,header,notes,350*i,0);
        event1->show();
    }
    for(int i = 0; i < 4; i++){
        Push* event1 = new Push(nullptr,header,notes,1100,200*i);
        event1->show();
    }

    for(int i = 0; i < 4; i++){
        Push* event1 = new Push(nullptr,header,notes,350*i,700);
        event1->show();
    }

    for(int i = 0; i < 4; i++){
        Push* event1 = new Push(nullptr,header,notes,300*i,300*i);
        event1->show();
    }
}

void SpamEvent::Print(QString &out){
    out += "Type: Push\nDate: " + date.toString("dd.MM.yyyy") + "\nTime: " + time.toString("hh:mm") + "\nHeader: " + header + "\nFrequency: "
    + frequency + "\nNotes: " + notes + "\n\n";
}

void SpamEvent::Display(QListWidget* widget){
    QVariant v;
    v.setValue(this);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole,header);
    item->setData(Qt::UserRole, v);
    widget->addItem(item);
}

bool SpamEvent::Executed(){
    return executed;
}

bool SpamEvent::Muted(){
    return muted;
}

//======================================================================================================== Реализация countdown-уведомления

CountDownEvent::CountDownEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    date = inDate;
    time = inTime;
    header = inHeader;
    frequency = inFrequency;
    notes = inNotes;
    muted = false;
    executed = false;
}

void CountDownEvent::Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes){
    date = newDate;
    time = newTime;
    header = newHeader;
    frequency = newFrequency;
    notes = newNotes;
}

void CountDownEvent::Check(QDate inDate, QTime inTime){
    if(date == inDate && time.hour() == inTime.hour() && time.minute() == inTime.minute() && frequency == "One time"){
        Show();
        executed = true;
    }
}

void CountDownEvent::Mute(){
    muted = true;
}

void CountDownEvent::Unmute(){
    muted = false;
}

void CountDownEvent::Show(){
    QFile f(":/countdownlogs/countdowns.log");
    if(f.open(QIODevice::WriteOnly)){
        QString out = "";
        Print(out);
        std::string str = out.toStdString();
        const char* arr = str.c_str();
        f.write(arr);
        f.close();
    }
    notification* d = new notification(nullptr,header,notes);
    d->show();
    executed = true;
}

void CountDownEvent::Print(QString &out){
    out += "Type: Push\nDate: " + date.toString("dd.MM.yyyy") + "\nTime: " + time.toString("hh:mm") + "\nHeader: " + header + "\nFrequency: "
    + frequency + "\nNotes: " + notes + "\n\n";
}

void CountDownEvent::Display(QListWidget* widget){
    QVariant v;
    v.setValue(this);
    QListWidgetItem* item = new QListWidgetItem();
    item->setData(Qt::DisplayRole,"Countdown event");
    item->setData(Qt::UserRole, v);
    widget->addItem(item);
}

bool CountDownEvent::Executed(){
    return executed;
}

bool CountDownEvent::Muted(){
    return muted;
}
