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
	//window.showMaximized();
	//window.showNormal();
 	window.showFullScreen();
 	//window.setFixedSize(500,500);

  //show message on console.
	qDebug() << "\nStart successful\n";


	return app.exec();
}
