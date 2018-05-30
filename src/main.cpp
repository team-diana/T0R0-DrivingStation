#include "window.h"
#include <QApplication>
#include <QGst/Init>

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("T0R0 GUI DRIVING STATION");
    QApplication app(argc, argv);
    QGst::init(&argc, &argv);

    Window window;
    window.showFullScreen();


    //show message on console.
    qDebug() << "\nWindow opened successfully\n";


    window.startVideo();

    qDebug() << "\nVideo started successfully\n";

    return app.exec();
}
#include "main.moc"
