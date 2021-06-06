#include "phabric.h"

IEvent* PushEventPhabric::CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    return new PushEvent(inDate,inTime,inHeader,inFrequency,inNotes);
}

IEvent* DialogEventPhabric::CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    return new DialogEvent(inDate,inTime,inHeader,inFrequency,inNotes);
}

IEvent* SpamEventPhabric::CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    return new SpamEvent(inDate,inTime,inHeader,inFrequency,inNotes);
}

IEvent* CountDownEventPhabric::CreateEvent(QDate inDate, QTime inTime, QString inHeader, QString inFrequency, QString inNotes){
    return new CountDownEvent(inDate,inTime,inHeader,inFrequency,inNotes);
}
