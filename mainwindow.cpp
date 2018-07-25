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
#include "gamepad.h"
#include <QTcpServer>

// Constructor
MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    ui = new WindowUi(this);

    //JOYSTICK://
    jstick = new Joystick(this, JOYSTICK_PATH);
    //Joystick is a thread so we have to start it:
    jstick->start();


    //////////

    //GAMEPAD://
    gamepad = new Gamepad(this, GAMEPAD_PATH);
    //Joystick is a thread so we have to start it:
    gamepad->start();

    //joystick_tcp = new TcpHarbinger();
    // Generic Signal from Gamepad
    connect(gamepad, &Gamepad::ButtonUpdate, this, &MainWindow::GamepadChangeText_Button);
    connect(gamepad, &Gamepad::AxisUpdate, this, &MainWindow::GamepadChangeText_Axis);

    // MOBILITY Signal from Gamepad
    connect(gamepad, &Gamepad::L3YUpdate, this, &MainWindow::mobilityLeftUpdate);
    connect(gamepad, &Gamepad::R3YUpdate, this, &MainWindow::mobilityRightUpdate);


    // Generic Signal from Joystick
    connect(jstick, &Joystick::ButtonUpdate, this, &MainWindow::ChangeText_Button);
    connect(jstick, &Joystick::AxisUpdate, this, &MainWindow::ChangeText_Axis);

    // ARM Signal from Joystick
    connect(joystick, &Joystick::pitchAxisUpdate, this, &MainWindow::shoulderUpdate);
    connect(joystick, &Joystick::yawAxisUpdate, this, &MainWindow::slewinGearUpdate);
    connect(joystick, &Joystick::rollAxisUpdate, this, &MainWindow::elbowUpdate);
    connect(joystick, &Joystick::throttleAxisUpdate, this, &MainWindow::pinchUpdate);

    connect(joystick, &Joystick::dpadLRAxisUpdate, this, &MainWindow::wristBendUpdate);
    connect(joystick, &Joystick::dpadUDAxisUpdate, this, &MainWindow::wristBendUpdate);

    //connect(joystick, &Joystick::fireButtonUpdate, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::thumbButtonUpdate, this, &MainWindow::GamepadChangeText_Button);
    connect(joystick, &Joystick::ButtonUpdate3, this, &MainWindow::GamepadChangeText_Button);
    connect(joystick, &Joystick::ButtonUpdate4, this, &MainWindow::GamepadChangeText_Button);
    connect(joystick, &Joystick::ButtonUpdate5, this, &MainWindow::GamepadChangeText_Button);
    connect(joystick, &Joystick::ButtonUpdate6, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate7, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate8, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate9, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate10, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate11, this, &MainWindow::GamepadChangeText_Button);
    //connect(joystick, &Joystick::ButtonUpdate12, this, &MainWindow::GamepadChangeText_Button);
    //////////

    //** TCP HARBINGERS **/
    gamepad_tcp = new TcpHarbinger(this, IP_ROVER, PORT_MOTORS_START, N_MOTORS);
    gamepad_tcp->start();   // Start thread

    arm_tcp = new TcpHarbinger(this, IP_ROVER, PORT_ARM_START, ARM_N_ACTUATORS);
    arm_tcp->start();
}

MainWindow::~MainWindow(){
    //Stop thread:
    jstick->stop();
    jstick->wait();

    gamepad_tcp->stopLoop();
    arm_tcp->stopLoop();

    delete ui;
}

//JOYSTICK://
void MainWindow::ChangeText_Button(int n, int pressed) {
    QString txt = QString("Button %1 is %2").arg(
                QString::number(n),
                pressed == 0 ? "up" : "down");

    ui->jstick_lbl->setText(txt);

    switch (n) {
        /* First wrist rotary gear*/
        case JOYSTICK_3:
            if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, -32768);
            else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
            break;

        case JOYSTICK_4:
            if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, 32767);
            else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
            break;

        /* Second wrist rotary gear*/
        case JOYSTICK_5:
            if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT2, -32768);
            else         arm_tcp->writeData16(ARM_WRIST_ROT2, 0);
            break;

        case JOYSTICK_6:
            if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT2, 32767);
            else         arm_tcp->writeData16(ARM_WRIST_ROT2, 0);
            break;
    }
}

void MainWindow::ChangeText_Axis(int n, int position) {
    QString txt = QString("Axis %1 is at position %2").arg(
                QString::number(n),
                QString::number(position));

    ui->jstick_lbl->setText(txt);

    /* DEPRECATED
    switch (n) {
        case JOYSTICK_PITCH:
            arm_tcp->writeData16(ARM_SHOULDER, position);
            break;

        case JOYSTICK_ROLL:
            arm_tcp->writeData16(ARM_ELBOW, position);
            break;

        case JOYSTICK_YAW:
            arm_tcp->writeData16(ARM_SLEAWINGGEAR, position);
            break;

        case JOYSTICK_THROTTLE:
            if      (position < -30000) arm_tcp->writeData16(ARM_PINCH, -32768);
            else if (position >  30000) arm_tcp->writeData16(ARM_PINCH,  32767);
            else                        arm_tcp->writeData16(ARM_PINCH,      0);
            break;

        case JOYSTICK_ARROWLR:
            arm_tcp->writeData16(ARM_WRIST_BEND, position);
            break;

        case JOYSTICK_ARROWUD:
            arm_tcp->writeData16(ARM_WRIST_BEND, position);
            break;
        }
        */
}
//////////

//* ARM *//
void MainWindow::shoulderUpdate(int position)
{
    arm_tcp->writeData16(ARM_SHOULDER, position);
}
void MainWindow::elbowUpdate(int position)
{
    arm_tcp->writeData16(ARM_SHOULDER, position);
}
void MainWindow::slewinGearUpdate(int position)
{
    arm_tcp->writeData16(ARM_SHOULDER, position);
}
void MainWindow::pinchUpdate(int position)
{
    arm_tcp->writeData16(ARM_SHOULDER, position);
}
void MainWindow::wristBendUpdate(int position)
{
    arm_tcp->writeData16(ARM_SHOULDER, position);
}
void MainWindow::rot1CounterClockWiseUpdate(int pressed)
{
    if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, -32768);
    else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
}
void MainWindow::rot1ClockWiseUpdate(int pressed)
{
    if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, 32767);
    else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
}
void MainWindow::rot2CounterClockWiseUpdate(int pressed)
{
    if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, -32768);
    else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
}
void MainWindow::rot2ClockWiseUpdate(int pressed)
{
    if (pressed) arm_tcp->writeData16(ARM_WRIST_ROT1, 32767);
    else         arm_tcp->writeData16(ARM_WRIST_ROT1, 0);
}
//////////

/* MOBILITY */
void MainWindow::mobilityLeftUpdate(int position)
{
    qDebug() << "Write throttle value for LEFT motors: " << position;
    gamepad_tcp->writeData16(MOTOR_FRONT_LEFT, position);
    gamepad_tcp->writeData16(MOTOR_REAR_LEFT,  position);
}
void MainWindow::mobilityRightUpdate(int position)
{
    qDebug() << "Write throttle value for RIGHT motors:" << position;
    gamepad_tcp->writeData16(MOTOR_FRONT_RIGHT, position);
    gamepad_tcp->writeData16(MOTOR_REAR_RIGHT,  position);
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
    /* DEPRECATED
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
    */
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
