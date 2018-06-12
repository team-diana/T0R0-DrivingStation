#include "window.h"
#include "ui.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QKeyEvent>

#include "qtcpclient.h"

//JOYSTICK//
#include "joystick.h"
#include <QTcpServer>



// Constructor
Window::Window(QWidget *parent) : QWidget(parent)
{
  ui = new WindowUi(this);

  // TCP CLIENT //
  QTcpClient client;
  client.connect("127.0.0.1", 50100);

  //QTcpSocket t;
  //t.connectToHost("127.0.0.1", 9000);

  //INPUT://
  jstick = new Joystick(this);
  //Joystick is a thread so we have to start it:
  jstick->start();

  connect(jstick, &Joystick::ButtonUpdate, this, &Window::ChangeText_Button);
  connect(jstick, &Joystick::AxisUpdate, this, &Window::ChangeText_Axis);
  //////////
}

Window::~Window(){
  //Stop thread:
  jstick->stop();
  jstick->wait();
  delete ui;
}

// TCP //
void Window::connectTcp()
{
    QByteArray data; // <-- fill with data

    _pSocket = new QTcpSocket( this ); // <-- needs to be a member variable: QTcpSocket * _pSocket;
    connect( _pSocket, SIGNAL(readyRead()), this, SLOT(readTcpData()) );

    _pSocket->connectToHost("127.0.0.1", 9000);
    if( _pSocket->waitForConnected() ) {
        _pSocket->write( data );
    }
}

void Window::readTcpData()
{
    QByteArray data = pSocket->readAll();
}

//INPUT://
void Window::ChangeText_Button(int n, int pressed){
  QString txt = QString("Button %1 is %2").arg(
                    QString::number(n),
                    pressed == 0 ? "up" : "down");
  ui->jstick_lbl->setText(txt);
}

void Window::ChangeText_Axis(int n, int position){
  QString txt = QString("Axis %1 is at position %2").arg(
                    QString::number(n),
                    QString::number(position));
  ui->jstick_lbl->setText(txt);
}

//////////

void Window::keyPressEvent (QKeyEvent *keyevent) {

  // CTRL + ALT + Q --> Quit the setApplicationName
  // R --> reload

	switch ( keyevent->key() ) {
	        case Qt::Key_R:                               // reload
	            qDebug("Pressed R");
	            update();
	            break;
	        case Qt::Key_Q:
              qDebug("Pressed Q");
	            key[0] = 1;
	            break;
         case Qt::Key_Alt:
              qDebug("Pressed Alt");
              key[1] = 1;
              break;
         case Qt::Key_Control:
              qDebug("Pressed Ctrl");
              key[2] = 1;
              break;

	    }

      if (key[0] && key[1] && key[2])
      {
        qDebug("Ctrl-Alt-Q all Pressed");
        QCoreApplication::quit();
      }
}

void Window::keyReleaseEvent (QKeyEvent *keyevent) {
  switch ( keyevent->key() ) {
        case Qt::Key_Q:
            qDebug("Released Q");
            key[0] = 0;
            break;
        case Qt::Key_Alt:
            qDebug("Released Alt");
            key[1] = 0;
            break;
        case Qt::Key_Control:
            qDebug("Released Ctrl");
            key[2] = 0;
            break;

      }
}
