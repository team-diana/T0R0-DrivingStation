#ifndef TCPSERVERHARBINGER_H
#define TCPSERVERHARBINGER_H

#include <QObject>
#include <QWidget>
#include <QThread>

#include "TcpClient.h"
#include "config.h"

/*
* nBytes = 1 or nBytes = 2 for the moment
*/
class TcpServerHarbinger : public QThread
{
    Q_OBJECT

public:
    explicit TcpServerHarbinger(QWidget *parent = 0, const char* _address = "127.0.0.1", int startPort = 8080, int _nConnections = 1);
    ~TcpServerHarbinger();

    void stopLoop();        // Stop tcpLoop()
    void resume();
    void suspend();

    int writeData16(int connectionId, int16_t value);

    int16_t readLastAxisValue (int axis);

protected:
    void run();

private:
    int nConnections, startPort;

    TcpClient *vecServer[10];

    uint16_t  vecData16[10];

    bool m_loop;
    bool m_wait;
};

#endif // TCPSERVERHARBINGER_H
