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
    void writeAxis ();

private:
    int nAxis, startPortAxis, startPortButton, nButton;
    uint16_t  *dataxis[10], *dataButton[20];;
    TcpClient *clientAxis[10], *clientButton[20];
};

#endif // TCPHARBINGER_H
