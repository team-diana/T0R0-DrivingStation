#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QGst/Init>
#include "dgamepadmonitor.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("T0R0 GUI DRIVING STATION");
    QApplication app(argc, argv);
    QGst::init(&argc, &argv);

    MainWindow mainwindow;
    mainwindow.showFullScreen();

    //show message on console.
    qDebug() << "\nWindow opened successfully\n";

    GamepadMonitor monitor;

    return app.exec();
}
