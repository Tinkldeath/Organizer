#ifndef ORGANIZER_H
#define ORGANIZER_H

#include <QMainWindow>
#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include "addevent.h"
#include "event.h"
#include "publisher.h"
#include "phabric.h"
#include "editevent.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Organizer; }
QT_END_NAMESPACE

class Organizer : public QMainWindow
{
    Q_OBJECT

public:
    Organizer(QWidget *parent = nullptr);
    ~Organizer();

private slots:

    void select_event(const QModelIndex &ind);

    void on_addEventButton_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_saveAndExitButton_clicked();

    void on_changeEventButton_clicked();

    void on_deleteEventButton_clicked();

    void on_radioDisableAllButton_clicked();

    void on_radioEnableAllButton_clicked();

    void CheckEvent();

    void on_startCountButton_clicked();

    void on_stopCountButton_clicked();

    void on_aboutButton_clicked();

private:
    void Parse();
    void Save();
    QTimer* timer;
    QMessageBox* message;
    Ui::Organizer *ui;
    EditEvent* editEvent;
    IEvent* selectedEvent;
    IEvent* countdownEvent;
    IPublisher* publisher;
};
#endif // ORGANIZER_H
