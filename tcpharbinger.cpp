#include "tcpharbinger.h"



TcpHarbinger::TcpHarbinger(QWidget *parent, Joystick *inputHid, const char* address, int _startPortAxis, int _nAxis, int _startPortButton, int _nButton)  : QWidget(parent)
{
    nAxis = _nAxis;
    startPortAxis = _startPortAxis;
    startPortButton = _startPortButton;
    nButton = _nButton;

    // Create TCP connection for each axis
    for (int i=0; i < nAxis; i++) {
      clientAxis[i] = new TcpClient(address, startPortAxis + i);
    }
    // Initialize Axis to zero
    for (int i=0; i < nAxis; i++) {
        clientAxis[i]->send16(32767);   // Initialize to neutral value (= 32767)
    }

}

TcpHarbinger::~TcpHarbinger()
{

}

void tcpLoop () {

  while (true)  // Loop
  {
    for (int i=0; i < nAxis; i++) {     // Read data array and send trough TCP
        clientAxis[i]->send16(dataAxis[i]);
    }
    usleep(100000); // Microseconds
  }
}

void writeAxis (int axis, int16_t value)
{
  dataAxis[axis] = value;
}
