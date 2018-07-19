#ifndef TCPHARBINGER_H
#define TCPHARBINGER_H

#include <QObject>
#include <QWidget>

#include "TcpClient.h"
#include "joystick.h"
#include "config.h"

// nBytes = 1 or nBytes = 2 for the moment

class TcpHarbinger : public QObject
{
    Q_OBJECT

public:
    explicit TcpHarbinger(QWidget *parent = 0, const char* address = "127.0.0.1", int startPort = 8080, int _nConnections = 1);
    ~TcpHarbinger();

    void startLoop();
    void stopLoop();        // Stop tcpLoop()
    void resume();
    void suspend();

    int writeAxis(int axis, int16_t value);

    int16_t readLastAxisValue (int axis);

private:
    int nConnections, startPort;

    TcpClient *vecClients[10];

    uint16_t  vecData16[10];

    bool m_loop;
    bool m_wait;
};

#endif // TCPHARBINGER_H
