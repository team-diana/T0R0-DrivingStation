#include "joystickdisplay.h"
#include <QDebug>
#include "inputmapping.h"

JoystickDisplay::JoystickDisplay(QWidget *parent) : QWidget(parent)
{
    joystickhandler = new JoystickHandler(this, THISIS_JOYSTICK);
    joystickhandler->start();
}

JoystickDisplay::~JoystickDisplay()
{
    //joystickhandler->stop();
}


void JoystickDisplay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QColor(255,0,0,255));
    painter.setBrush(QColor(4,4,4,255));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    painter.drawText(QPoint(10,16), QString("JOYSTICK"));

    bar1 = new Bar (this);
    bar1->setGeometry(228, 25, 13, 221);
    bar1->show();

    bar1->setPerc(joystickhandler->getAxisValue(JOYSTICK_THROTTLE));

    cGraph = new CrossGraph (this);
    cGraph->setGeometry(0, 25, 221, 221);
    cGraph->show();
    cGraph->setX(joystickhandler->getAxisValue(JOYSTICK_ROLL));
    cGraph->setY(joystickhandler->getAxisValue(JOYSTICK_PITCH));
}


