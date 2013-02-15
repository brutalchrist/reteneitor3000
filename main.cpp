#include <QtGui/QApplication>
#include "reteneitor3000.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    reteneitor3000 w;
    w.show();

    return a.exec();
}
