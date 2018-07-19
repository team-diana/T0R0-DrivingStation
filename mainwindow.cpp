#include "mainwindow.h"
#include "ui.h"
#include "config.h"
#include "inputmapping.h"
#include "mathfunctions.h"

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

    //joystick_tcp = new TcpHarbinger();

    //gamepad_tcp->start();     // CRASHES IF UNCOMMENTED  |  DEPRECATED
    gamepad_tcp = new TcpHarbinger(this, IP_ROVER, PORT_MOTORS_START, N_MOTORS);
    //gamepad_tcp->startLoop();

    connect(gamepad, &Joystick::ButtonUpdate, this, &MainWindow::GamepadChangeText_Button);
    connect(gamepad, &Joystick::AxisUpdate, this, &MainWindow::GamepadChangeText_Axis);
    //////////
}

MainWindow::~MainWindow(){
    //Stop thread:
    jstick->stop();
    jstick->wait();

    gamepad_tcp->stopLoop();

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

    // Collect data to be send to the motors
    gamepad_tcp->suspend();
    switch (n) {
        case GAMEPAD_L3Y:   // LEFT MOTORS
            qDebug() << "Write throttle value for LEFT motors: " << position;
            gamepad_tcp->writeData16(MOTOR_FRONT_LEFT, position);
            gamepad_tcp->writeData16(MOTOR_REAR_LEFT,  position);
            break;

        case GAMEPAD_R3Y:   // RIGHT MOTORS
            qDebug() << "Write throttle value for RIGHT motors:" << position;
            gamepad_tcp->writeData16(MOTOR_FRONT_RIGHT, position);
            gamepad_tcp->writeData16(MOTOR_REAR_RIGHT,  position);
            break;

        default:
            break;
    }
    gamepad_tcp->resume();
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
