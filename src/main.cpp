#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
//#include "KeyPress.h"

#include "window.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);

	QDesktopWidget *desktop = app.desktop();

	Window window(desktop->screenGeometry());
 	window.showFullScreen();

  //show message on console.
	qDebug() << "\nStart successful\n";


	return app.exec();
}
