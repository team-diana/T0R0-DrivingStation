#include "motors.h"

//* SINGLE MOTOR *//
Motor::Motor (QWidget *parent, int16_t _throttle) : QWidget(parent)
{
    throttle = _throttle;
}

Motor::~Motor ()
{

}

int16_t readThrottle ()
{
    return throttle;
}

void writeThrottle (int16_t _thrtl)
{
    throttle = _thrtl;
}
