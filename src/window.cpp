#include "window.h"

//Video player test:
#include "player.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QLabel>
#include <QBoxLayout>

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


  //VIdeo player test://
  player = new Player(this);
  connect(player, SIGNAL(positionChanged()), this, SLOT(onPositionChanged()));
  connect(player, SIGNAL(stateChanged()), this, SLOT(onStateChanged()));
  player->setMouseTracking(true);

  label = new QLabel();
  label->setText("Video\n");

  QVBoxLayout *appLayout = new QVBoxLayout;
  appLayout->setContentsMargins(0, 0, 0, 0);
  appLayout->addWidget(player);
  appLayout->addWidget(label);
  appLayout->addWidget(pixlogo);
  setLayout(appLayout);
  /////////////////////
}

Window::~Window()
{
  delete player;
}

//VIDEO PLAYER TEST://
void Window::openFile(const QString & filename){
    player->stop();
    player->setUri(filename);
    player->play();
}
//////////////////////

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
