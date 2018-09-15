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

    painter.setPen(QColor(100,190,250,255));
    painter.setBrush(QColor(4,4,4,255));
    painter.drawRect(0, 0, this->width()-1, this->height()-1);
    painter.drawText(QPoint(7,17), QString("ARM"));

    barThrottle = new Bar (this, 0);
    barThrottle->setGeometry(234, 25, 13, 221);
    barThrottle->show();

    barThrottle->setPerc(int16ToPerc(joystickhandler->getAxisValue(JOYSTICK_THROTTLE)));


    barYaw = new Bar (this, 1);
    barYaw->setGeometry(5, 253, 221, 13);
    barYaw->show();

    barYaw->setPerc( int16ToPerc( joystickhandler->getAxisValue(JOYSTICK_YAW) )  );

    cGraph = new CrossGraph (this);
    cGraph->setGeometry(5, 25, 221, 221);
    cGraph->show();
    cGraph->setX( int16ToPerc( joystickhandler->getAxisValue(JOYSTICK_PITCH)  )  );
    cGraph->setY( int16ToPerc( joystickhandler->getAxisValue(JOYSTICK_ROLL) )  );
}


int JoystickDisplay::int16ToPerc(int16_t value)
{
    int res = 0;

    uint16_t uval = value + 32768;
    res = (uval / 65535.0) * 100.0;

    //qDebug() << " >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> " << res;

    return res;
}
