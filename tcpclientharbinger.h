#ifndef TCPCLIENTHARBINGER_H
#define TCPCLIENTHARBINGER_H

#include <QObject>
#include <QWidget>
#include <QThread>

#include "TcpClient.h"
#include "config.h"

/*
* nBytes = 1 or nBytes = 2 for the moment
*/
class TcpClientHarbinger : public QThread
{
    Q_OBJECT

public:
    explicit TcpClientHarbinger(QWidget *parent = 0, const char* _address = "127.0.0.1", int startPort = 8080, int _nConnections = 1);
    ~TcpClientHarbinger();

    void stopLoop();        // Stop tcpLoop()
    void resume();
    void suspend();

    int writeData16(int connectionId, int16_t value);

    int16_t readLastAxisValue (int axis);

protected:
    void run();

private:
    int nConnections, startPort;

    TcpClient *vecClients[10];

    uint16_t  vecData16[10], vecDataOld[10];

    bool m_loop;
    bool m_wait;
    const char* address;
};

#endif // TCPCLIENTHARBINGER_H
