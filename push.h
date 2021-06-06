#ifndef PUSH_H
#define PUSH_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class Push;
}

class Push : public QWidget
{
    Q_OBJECT

public:
    explicit Push(QWidget *parent = nullptr, QString header = "", QString notes = "", int x = 0, int y = 0);
    ~Push();

private slots:

    void on_closeButton_clicked();

private:
    Ui::Push *ui;
    QTimer* timer;
};

#endif // PUSH_H
