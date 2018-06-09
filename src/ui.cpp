#include "ui.h"
#include "voipvideowidget.h"

#include <QDebug>
#include <QString>
#include <QLabel>


// Constructor
WindowUi::WindowUi(QWidget *parent) : QWidget(parent)
{
  CreateUI();

  //Gstremer://
  //Set port of the camera
  camera1_videoWidget->setPort(1234);

  //START VIDEO
  camera1_videoWidget->startPipeline();

  qDebug() << "\nVideo started successfully\n";

  /////////////
}
///////

WindowUi::~WindowUi(){
}

//UI://
void WindowUi::CreateUI(){
  this->setGeometry(0, 0, 1920, 1080);

  // set black background
  QPalette pal = palette();

	// Set backgroud color
	pal.setColor(QPalette::Background, QColor(14,14,14,255));
  this->setAutoFillBackground(true);
  this->setPalette(pal);


	// Show Team D.I.A.N.A. logo at bottom-right
  //add images to resources.qrc to use them//
  // http://doc.qt.io/qt-5/resources.html //
	QLabel *pixlogo = new QLabel(this);
  QPixmap pixmaplogo(":/Images/diana-logo-193x90.png");
  int w = 193;
  int h = 90;
	pixlogo->setPixmap(pixmaplogo.scaled(w, h, Qt::KeepAspectRatio));
	pixlogo->setGeometry( this->width() - 238, this->height() - 120, w, h );

  //Gstremer://
  camera1_videoWidget = new VoipVideoWidget(this);
  camera1_videoWidget->setGeometry( (this->width()-960)/2, (this->height()-600)/2, 960, 600 );
  /////////////

  //INPUT://
  jstick_lbl = new QLabel(this);
  jstick_lbl->setGeometry(5, 5, 500, 50);
  jstick_lbl->setText("NO INPUT");
  jstick_lbl->setStyleSheet( "color : white;" );
  //////////
}
