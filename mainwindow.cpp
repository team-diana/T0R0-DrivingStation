#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QKeyEvent>
#include <QTcpServer>

#include "mainwindow.h"
#include "ui.h"
#include "config.h"
#include "inputmapping.h"
#include "mathfunctions.h"

// Constructor
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    ui = new WindowUi(this);

    gamepadhandler = new JoystickHandler(this, THISIS_GAMEPAD);
    gamepadhandler->start();
}

MainWindow::~MainWindow(){
    //Stop thread:
    //gamepadhandler->stop();

    delete ui;
}

//JOYSTICK://
void MainWindow::ChangeText_Button(int n, int pressed) {
    QString txt = QString("Button %1 is %2").arg(
                QString::number(n),
                pressed == 0 ? "up" : "down");

    ui->jstick_lbl->setText(txt);
}

void MainWindow::ChangeText_Axis(int n, int position) {
    QString txt = QString("Axis %1 is at position %2").arg(
                QString::number(n),
                QString::number(position));

    ui->jstick_lbl->setText(txt);
}
//////////

/* MOBILITY */
void MainWindow::mobilityLeftUpdate(double position)
{
    int16_t data = (int16_t) (position * 32767.4);
    qDebug() << "Write throttle value for LEFT motors: " << data;
    gamepad_tcp->writeData16(MOTOR_FRONT_LEFT, data);
    gamepad_tcp->writeData16(MOTOR_REAR_LEFT,  data);
}
void MainWindow::mobilityRightUpdate(double position)
{
    int16_t data = (int16_t) (position * 32767.4);
    qDebug() << "Write throttle value for RIGHT motors:" << data;
    gamepad_tcp->writeData16(MOTOR_FRONT_RIGHT, data);
    gamepad_tcp->writeData16(MOTOR_REAR_RIGHT,  data);
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
}
//////////

//* KEYBOARD *//
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
//////////
