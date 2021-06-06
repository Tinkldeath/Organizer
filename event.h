#ifndef EVENT_H
#define EVENT_H

#include <QDate>
#include <QTime>
#include <QFile>
#include "push.h"
#include "notification.h"
#include <QListWidget>
#include <cmath>

//========================================================================================================== Абстрактный класс события
class Event
{
protected:
    QDate date;
    QTime time;
    QString header;
    QString frequency;
    QString notes;
    bool executed;
    bool muted;
};

//========================================================================================================== Интерфейс события
class IEvent
{
public:
    virtual void Check(QDate inDate, QTime inTime) = 0;
    virtual void Mute() = 0;
    virtual void Unmute() = 0;
    virtual void Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes) = 0;
    virtual void Print(QString &out) = 0;
    virtual void Display(QListWidget* widget) = 0;
    virtual bool Executed() = 0;
    virtual bool Muted() = 0;
    virtual QDate GetDate() = 0;
    virtual QTime GetTime() = 0;
    virtual QString GetHeader() = 0;
    virtual QString GetFrequency() = 0;
    virtual QString GetNotes() = 0;
protected:
    virtual void Show() = 0;
};


//========================================================================================================== Конкретные события
class PushEvent : public IEvent, public Event
{
public:
    PushEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes);
    void Check(QDate inDate, QTime inTime) override;
    void Mute() override;
    void Unmute() override;
    void Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes) override;
    void Print(QString &out) override;
    void Display(QListWidget* widget) override;
    bool Executed() override;
    bool Muted() override;
    QDate GetDate() override { return date; }
    QTime GetTime() override { return time; }
    QString GetHeader() override { return header; }
    QString GetFrequency() override { return frequency; }
    QString GetNotes() override { return notes; }
private:
    void Show() override;
};

class DialogEvent : public IEvent, public Event
{
public:
    DialogEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes);
    void Check(QDate inDate, QTime inTime) override;
    void Mute() override;
    void Unmute() override;
    void Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes) override;
    void Print(QString &out) override;
    void Display(QListWidget* widget) override;
    bool Executed() override;
    bool Muted() override;
    QDate GetDate() override { return date; }
    QTime GetTime() override { return time; }
    QString GetHeader() override { return header; }
    QString GetFrequency() override { return frequency; }
    QString GetNotes() override { return notes; }
private:
    void Show() override;
};

class SpamEvent : public IEvent, public Event
{
public:
    SpamEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes);
    void Check(QDate inDate, QTime inTime) override;
    void Mute() override;
    void Unmute() override;
    void Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes) override;
    void Print(QString &out) override;
    void Display(QListWidget* widget) override;
    bool Executed() override;
    bool Muted() override;
    QDate GetDate() override { return date; }
    QTime GetTime() override { return time; }
    QString GetHeader() override { return header; }
    QString GetFrequency() override { return frequency; }
    QString GetNotes() override { return notes; }
private:
    void Show() override;
};

class CountDownEvent : public IEvent, public Event
{
public:
    CountDownEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes);
    void Check(QDate inDate, QTime inTime) override;
    void Mute() override;
    void Unmute() override;
    void Change(QDate newDate, QTime newTime, QString newHeader, QString newFrequency, QString newNotes) override;
    void Print(QString &out) override;
    void Display(QListWidget* widget) override;
    bool Executed() override;
    bool Muted() override;
    QDate GetDate() override { return date; }
    QTime GetTime() override { return time; }
    QString GetHeader() override { return header; }
    QString GetFrequency() override { return frequency; }
    QString GetNotes() override { return notes; }
private:
    void Show() override;
};

#endif // EVENT_H
