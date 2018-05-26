#include "window.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QLabel>
#include <QBoxLayout>

//LibVLC://
#include <QFileDialog>
#include <QInputDialog>

#include <VLCQtCore/Common.h>
#include <VLCQtCore/Instance.h>
#include <VLCQtCore/Media.h>
#include <VLCQtCore/MediaPlayer.h>
////////////

// Constructor
Window::Window(QRect screen, QWidget *parent) : QWidget(parent)
{
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
	pixlogo->setPixmap(pixmaplogo.scaled(193, 90, Qt::KeepAspectRatio));
	pixlogo->setGeometry( this->width() - 238, this->height() - 120, 193, 90 );

  connected = false;

  //LibVLC://
  _instance = new VlcInstance(VlcCommon::args(), this);
  _player = new VlcMediaPlayer(_instance);
  ///////////
}

Window::~Window(){
  delete _player;
  delete _media;
  delete _instance;
}

//LibVLC://
void Window::openLocal()
{
   QString file =
           QFileDialog::getOpenFileName(this, tr("Open file"),
                                        QDir::homePath(),
                                        tr("Multimedia files(*)"));
   if (file.isEmpty())
       return;
   _media = new VlcMedia(file, true, _instance);
   _player->open(_media);
}

void Window::openUrl()
{
   QString url =
           QInputDialog::getText(this, tr("Open Url"), tr("Enter the URL you want to play"));
   if (url.isEmpty())
       return;
   _media = new VlcMedia(url, _instance);
   _player->open(_media);
}
////////////

void Window::keyPressEvent (QKeyEvent *k) {
	switch ( tolower(char(k->key())) ) {
	        case 'r':                               // reload
	            qDebug("Pressed R");
	            update();
	            break;
	        case 'q':                               // quit
	            QCoreApplication::quit();
	            break;
	    }
}
