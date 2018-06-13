#include "window.h"
#include "ui.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QKeyEvent>



//JOYSTICK//
#include "joystick.h"
#include <QTcpServer>



// Constructor
Window::Window(QWidget *parent) : QWidget(parent)
{
  ui = new WindowUi(this);

  // TCP CLIENT //
  left_client = new TcpClient("127.0.0.1", 50100);
  right_client = new TcpClient("127.0.0.1", 50101);

  uint8_t left_command = 0;
  left_client->send8(left_command);

  uint8_t right_command = 0;
  right_client->send8(right_command);

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

  uint8_t speed[2] = {0, 0};

  if (position >= 0) // Right
  {
    speed[0] = 0;
    speed[1] = (uint8_t) (position / 128);
  }
  else  // Left
  {
    speed[1] = 0;
    speed[0] = (uint8_t) ((-position) / 128);
  }


  qDebug() << "Invio comandi motori (sinistro, destro):\t" << speed[0] << "\t" << speed[0];
  left_client->send8(speed[0]);
  right_client->send8(speed[1]);
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
