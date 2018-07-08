#include "mainwindow.h"
#include "ui.h"
#include "config.h"
#include "inputmapping.h"

#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QKeyEvent>

//JOYSTICK//
#include "joystick.h"
#include <QTcpServer>

// Constructor
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    ui = new WindowUi(this);

    // TCP CLIENT //
    left_client = new TcpClient(IP_ROVER, PORT_MOBILITY_LEFT);
    right_client = new TcpClient(IP_ROVER, PORT_MOBILITY_RIGHT);

    //uint16_t left_command = 0;
    //left_client->send16(left_command);

    //uint16_t right_command = 0;
    //right_client->send16(right_command);



    //uint16_t vec[10] = {0, 32768, 65535, 20123, 49654};

    //for (int i=0; i<5; i++) left_client->send16(vec[i]);


    //left_client->send16(0);
    left_client->send16(20123);
    //left_client->send16(32768);
    //left_client->send16(49654);
    //left_client->send16(65535);

    //JOYSTICK://
  jstick = new Joystick(this, JOYSTICK_PATH);
  //Joystick is a thread so we have to start it:
  jstick->start();

  connect(jstick, &Joystick::ButtonUpdate, this, &MainWindow::ChangeText_Button);
  connect(jstick, &Joystick::AxisUpdate, this, &MainWindow::ChangeText_Axis);
  //////////

  //GAMEPAD://
  gamepad = new Joystick(this, GAMEPAD_PATH);
  //Joystick is a thread so we have to start it:
  gamepad->start();

  connect(gamepad, &Joystick::ButtonUpdate, this, &MainWindow::GamepadChangeText_Button);
  connect(gamepad, &Joystick::AxisUpdate, this, &MainWindow::GamepadChangeText_Axis);


  //////////
}

MainWindow::~MainWindow(){
  //Stop thread:
  jstick->stop();
  jstick->wait();
  delete ui;
}

//JOYSTICK://
void MainWindow::ChangeText_Button(int n, int pressed){
  QString txt = QString("Button %1 is %2").arg(
                    QString::number(n),
                    pressed == 0 ? "up" : "down");
  ui->jstick_lbl->setText(txt);
}

void MainWindow::ChangeText_Axis(int n, int position){
  QString txt = QString("Axis %1 is at position %2").arg(
                    QString::number(n),
                    QString::number(position));
  ui->jstick_lbl->setText(txt);

  /* DEPRECATED *
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
  */
}

//////////

//* GAMEPAD *//
void MainWindow::GamepadChangeText_Button(int n, int pressed){
  QString txt = QString("Button %1 is %2").arg(
                    QString::number(n),
                    pressed == 0 ? "up" : "down");
  ui->gamepad_lbl->setText(txt);
}

void MainWindow::GamepadChangeText_Axis(int n, int position){
    QString txt = QString("Axis %1 is at position %2").arg(
                    QString::number(n),
                    QString::number(position));
    ui->gamepad_lbl->setText(txt);

    //uint8_t bytes[2] = {0, 0};
    uint16_t data = (uint16_t) position + 32768;

    if (n == GAMEPAD_L3Y) // Left
    {
        //left_client->send16( data );
        qDebug() << "Sent to Mobility Driver LEFT:\t" << data;
    }
    else if (n == GAMEPAD_R3Y) // Right
    {
        //right_client->send16( data);
        qDebug() << "Sent to Mobility Driver RIGHT:\t" << data;
    }
    else {      // EXPERIMENTAL
        data=32768;
        //left_client->send16( data );
        //right_client->send16( data );
    }



    n=-1;
    position=0;
    data=32768;
}
//////////

void MainWindow::keyPressEvent (QKeyEvent *keyevent) {

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

void MainWindow::keyReleaseEvent (QKeyEvent *keyevent) {
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
