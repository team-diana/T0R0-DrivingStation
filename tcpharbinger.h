#ifndef TCPHARBINGER_H
#define TCPHARBINGER_H

#include <QObject>
#include <QWidget>

#include "TcpClient.h"
#include "joystick.h"

class tcpHarbinger : public QWidget
{
    Q_OBJECT
public:
    explicit tcpHarbinger(QWidget *parent = 0, TcpClient *tcpclient = 0, Joystick *inputhid);
    ~tcpHarbinger();
};

#endif // TCPHARBINGER_H
