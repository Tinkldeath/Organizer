#include "editevent.h"
#include "ui_editevent.h"

EditEvent::EditEvent(QWidget *parent, QListWidget* list, IPublisher* publisher) :
    QDialog(parent),
    ui(new Ui::EditEvent)
{
    widget = list;
    pub = publisher;
    ui->setupUi(this);
    setWindowFlag(Qt::Tool);
    message = new QMessageBox();
}

EditEvent::~EditEvent()
{
    delete message;
    delete ui;
}

void EditEvent::on_cancelButton_clicked()
{
    close();
}

void EditEvent::SetEvent(IEvent *event){
    eventptr = event;
    ui->lineNewHeader->setText(event->GetHeader());
    ui->plainTextEdit->setPlainText(event->GetNotes());
    ui->calendarWidget->selectedDate().setDate(event->GetDate().year(),event->GetDate().month(),event->GetDate().day());
    ui->timeEdit->setTime(event->GetTime());
    show();
}

void EditEvent::on_confirmButton_clicked()
{
    if(ui->lineNewHeader->text() == ""){
        message->setText("Header is necessary field!");
        message->exec();
        return;
    }
    QDate newDate = ui->calendarWidget->selectedDate();
    QTime newTime = ui->timeEdit->time();
    QString newHeader = ui->lineNewHeader->text();
    QString newFrequency = ui->comboBox->currentText();
    QString newNotes = ui->plainTextEdit->toPlainText();
    eventptr->Change(newDate,newTime,newHeader,newFrequency,newNotes);
    message->setText("Changes confirmed");
    message->exec();
    widget->clear();
    pub->Display(widget);
    close();
}
