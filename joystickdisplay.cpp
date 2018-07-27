#include "joystickdisplay.h"
#include <QDebug>

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
    painter.drawText(QPoint(10,16), QString("TEST 1"));

    bar1 = new Bar (this);
    bar1->setGeometry(20, 20, this->width()-21, this->height()-21);
    bar1->show();

    bar1->setPerc(joystickhandler->getAxisValue(0));

    cGraph = new CrossGraph(this);
    cGraph->setGeometry(45, 45, 250, 250);
    cGraph->show();
}


