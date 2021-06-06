#ifndef ADDEVENT_H
#define ADDEVENT_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidget>
#include <QTimer>
#include "publisher.h"
#include "phabric.h"
#include "organizer.h"

namespace Ui {
class AddEvent;
}

class AddEvent : public QDialog
{
    Q_OBJECT

public:
    explicit AddEvent(QWidget *parent, IPublisher* publisher, QListWidget * list, QTimer *timer);
    ~AddEvent();
signals:
    void go_back();

private slots:
    void on_cancelButton_clicked();

    void on_addEventButton_clicked();

private:
    Ui::AddEvent* ui;
    IPublisher* pub;
    QMessageBox* message;
    QTimer* t;
    QListWidget* widget;
};

#endif // ADDEVENT_H
