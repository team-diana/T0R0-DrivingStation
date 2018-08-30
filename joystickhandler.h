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
    explicit JoystickHandler(QWidget *parent = nullptr, int _hidType = -1);
    ~JoystickHandler();

    int16_t getAxisValue(int axis);
    bool getButtonState(int button);

protected:
    void run();

private:
    QWidget *par;
    int hidType;
    Joystick *joystick;
    TcpHarbinger *arm_tcp, *mobility_tcp;

    void putAxisValue(int axis, int16_t value);
    void putButtonState(int button, bool state);

    int16_t axisesValues[10];
    bool buttonsState[20];

    static uint16_t inputRemap(uint16_t x, float a, float b, int c);
};

#endif // JOYSTICKHANDLER_H
