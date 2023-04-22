
#include "logindialog.h"
#include "kernel.h"
#include <QApplication>

#include <QTime>
#include "QDebug"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Kernel kernel;
    // qDebug() << QTime::currentTime().toString("hh_mm_ss_zzz");
    return a.exec();
}
