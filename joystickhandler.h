#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <QThread>
#include <unistd.h>
#include <QPaintEvent>

#include "joystick.hh"
#include "tcpharbinger.h"
#include "bar.h"

class JoystickHandler : public QThread
{
    Q_OBJECT

public:
    explicit JoystickHandler(QWidget *parent = nullptr);
    ~JoystickHandler();

protected:
    void run();

private:
    Bar *bar1;
    Joystick *joystick;
    TcpHarbinger *arm_tcp;
};

#endif // JOYSTICKHANDLER_H
