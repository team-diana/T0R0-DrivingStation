#include "tcpharbinger.h"



TcpHarbinger::TcpHarbinger(QWidget *parent, Joystick *inputHid, const char* address, int _startPortAxis, int _nAxis, int _startPortButton, int _nButton)  : QWidget(parent)
{
    nAxis = _nAxis;
    startPortAxis = _startPortAxis;
    startPortButton = _startPortButton;
    nButton = _nButton;

    m_loop = false;

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

  while (m_loop)  // Loop -> if  m_loop = true
  {
    for (int i=0; i < nAxis; i++) {     // Read data array and send trough TCP
        clientAxis[i]->send16(dataAxis[i]);
    }
    usleep(100000); // Microseconds
  }
}

void Joystick::stop()
{
  m_loop = false;
}

void writeAxis (int axis, int16_t value)
{
  dataAxis[axis] = (uint16_t) value + 32768;
}

void writeButton (int button, bool pressed)
{
    dataButton[button] = (bool) pressed;
}

int16_t readLastAxisValue (int axis)
{
    return (int16_t) dataAxis[axis] - 32768;
}

bool writeLastButtonState (int button)
{
    return (bool) dataButton[button];
}
