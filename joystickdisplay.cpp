#include "joystickdisplay.h"
#include <QDebug>

JoystickDisplay::JoystickDisplay(QWidget *parent) : QWidget(parent)
{
    joystickhandler = new JoystickHandler(this);
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
    qDebug() << "LOOK AT ME <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";

    bar1 = new Bar (this, 50, 10, 100);
    bar1->setGeometry(20, 20, 100, 100);
    //bar1->show();
}


