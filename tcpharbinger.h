#ifndef TCPHARBINGER_H
#define TCPHARBINGER_H

#include <QObject>
#include <QWidget>

#include "TcpClient.h"
#include "joystick.h"
#include "config.h"

// nBytes = 1 or nBytes = 2 for the moment

class TcpHarbinger : public QWidget
{
    Q_OBJECT

public:
    explicit TcpHarbinger(QWidget *parent = 0, Joystick *inputHid, const char* address, int startPortAxis, int nAxis, int startPortButton, int nButton);
    ~TcpHarbinger();

    void tcpLoop();
    void stop();        // Stop tcpLoop()

    void writeAxis(int axis, int16_t value);
    void writeButton(int button, bool pressed);

    int16_t readLastAxisValue (int axis);
    bool writeLastButtonState (int button);


private:
    int nAxis, startPortAxis, startPortButton, nButton;
    uint16_t  *dataxis[10];
    bool dataButton[20];
    TcpClient *clientAxis[10], *clientButton[20];

    bool m_loop;
};

#endif // TCPHARBINGER_H
