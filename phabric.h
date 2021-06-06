#ifndef PHABRIC_H
#define PHABRIC_H

#include "event.h"

//========================================================================================================== Абстрактная фабрика
class AbstractPhabric
{
public:
    virtual IEvent* CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes) = 0;
};


//========================================================================================================== Конкретные фабрики
class PushEventPhabric : public AbstractPhabric
{
public:
    IEvent* CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes) override;
};

class DialogEventPhabric : public AbstractPhabric
{
public:
    IEvent* CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes) override;
};

class SpamEventPhabric : public AbstractPhabric
{
public:
     IEvent* CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes) override;
};

class CountDownEventPhabric : public AbstractPhabric
{
public:
    IEvent* CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes) override;
};

#endif // PHABRIC_H
