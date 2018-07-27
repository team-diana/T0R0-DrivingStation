#include "gamepaddisplay.h"
#include <QDebug>
#include "inputmapping.h"

GamepadDisplay::GamepadDisplay(QWidget *parent) : QWidget(parent)
{
    gamepadhandler = new JoystickHandler(this, THISIS_GAMEPAD);
    gamepadhandler->start();
}

GamepadDisplay::~GamepadDisplay()
{
    //joystickhandler->stop();
}


void GamepadDisplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(100,190,250,255));
    painter.setBrush(QColor(4,4,4,255));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    painter.drawText(QPoint(7,17), QString("MOBILITY"));

    leftThrottle = new Bar (this, 0);
    leftThrottle->setGeometry(28, 25, 13, 221);
    leftThrottle->show();

    leftThrottle->setPerc(gamepadhandler->getAxisValue(GAMEPAD_L3Y));

    rightThrottle = new Bar (this, 0);
    rightThrottle->setGeometry(70, 25, 13, 221);
    rightThrottle->show();

    rightThrottle->setPerc(gamepadhandler->getAxisValue(GAMEPAD_R3Y));
}


