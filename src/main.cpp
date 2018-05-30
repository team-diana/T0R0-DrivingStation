#include "window.h"
#include <QApplication>
#include <QGst/Init>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QGst::init(&argc, &argv);

    Window window;
    window.show();
    window.startVideo();

    return app.exec();
}
#include "main.moc"
