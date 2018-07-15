#include "tcpharbinger.h"



TcpHarbinger::TcpHarbinger(QWidget *parent, Joystick *inputHid, const char* address, int startPortAxis, int nAxis, int startPortButton, int nButton)  : QWidget(parent)
{
    data16 =    0;
    client = new TcpClient(IP_ROVER, PORT_MOBILITY_FRONTLEFT);
}

TcpHarbinger::~TcpHarbinger()
{

}
