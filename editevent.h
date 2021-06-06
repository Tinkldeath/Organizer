#ifndef EDITEVENT_H
#define EDITEVENT_H

#include <QDialog>
#include <QMessageBox>
#include "event.h"
#include "publisher.h"

namespace Ui {
class EditEvent;
}

class EditEvent : public QDialog
{
    Q_OBJECT

public:
    explicit EditEvent(QWidget *parent, QListWidget* list, IPublisher* publisher);
    void SetEvent(IEvent* event);
    ~EditEvent();

private slots:
    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::EditEvent *ui;
    IEvent* eventptr;
    IPublisher* pub;
    QListWidget* widget;
    QMessageBox* message;
};

#endif // EDITEVENT_H
