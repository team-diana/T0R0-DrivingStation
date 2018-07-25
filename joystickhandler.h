#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <QThread>
#include "joystick.hh"
#include <unistd.h>
#include "tcpharbinger.h"

class JoystickHandler : public QThread
{
    Q_OBJECT

public:
    explicit JoystickHandler(QWidget *parent = nullptr);
    ~JoystickHandler();

protected:
    void run();

private:
    Joystick *joystick;
    TcpHarbinger *arm_tcp;
};

#endif // JOYSTICKHANDLER_H
