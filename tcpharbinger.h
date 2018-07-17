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
    explicit TcpHarbinger(QWidget *parent = 0, const char* address = "127.0.0.1", int startPortAxis = 8080, int nAxis = 1, int startPortButton = 8180, int nButton = 1);
    ~TcpHarbinger();

    void tcpLoop();
    void stop();        // Stop tcpLoop()

    int writeAxis(int axis, int16_t value);
    int writeButton(int button, bool pressed);

    int16_t readLastAxisValue (int axis);
    bool writeLastButtonState (int button);


private:
    int nAxis, startPortAxis, startPortButton, nButton;
    uint16_t  dataAxis[10];
    bool dataButton[20];
    TcpClient *clientAxis[10], *clientButton[20];

    bool m_loop;
};

#endif // TCPHARBINGER_H
