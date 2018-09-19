#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug()<<"present a";
    MainWindow w;
    qDebug()<<"present w";
    w.show();
    qDebug()<<"w show";
    return a.exec();
}
