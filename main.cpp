#include "organizer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/src/icon.ico"));
    Organizer w;
    w.show();
    return a.exec();
}
