#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
//Gstreamer:
#include <QGst/Init>

#include "window.h"
//#include "mediapp.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	//QT Gstreamer initialization:
  QGst::init(&argc, &argv);

	QDesktopWidget *desktop = app.desktop();

	Window window(desktop->screenGeometry());
	if(argc==2) window.openFile(argv[1]);
 	window.showFullScreen();

  //show message on console.
	qDebug() << "\nWindow opened successfully\n";

	/*
  MediaApp media;
  media.show();
  if (argc == 2) {
      media.openFile(argv[1]);

			qDebug() << "Successfully opened file \"" << (argv[1]) << "\"\n";
  }
	else qDebug() <<"Use the command line to give a file name.\n";
	*/

	return app.exec();
}
