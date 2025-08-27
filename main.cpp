#include "reqmon.h"
#include "space.h"

#include <QApplication>
#include <QStackedWidget>

#include "reqmon.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStackedWidget wstack;

    Space *mainw = new Space;


#ifdef QT_DEBUG
    ReqMon mon;
    mon.setWindowFlags(Qt::Tool);
    mon.show();
#endif
    mainw->show();

    return a.exec();
}
