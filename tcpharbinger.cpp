#include "tcpharbinger.h"



TcpHarbinger::TcpHarbinger(QWidget *parent, Joystick *inputHid, const char* address, int _startPortAxis, int _nAxis, int _startPortButton, int _nButton)  : QWidget(parent)
{
    nAxis = _nAxis;
    startPortAxis = _startPortAxis;
    startPortButton = _startPortButton;
    nButton = _nButton;

    m_loop = true;

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

int writeAxis (int axis, int16_t value)
{
  int retStatus = 0;
  if (axis < nAxis && axis >= 0)
    dataAxis[axis] = (uint16_t) value + 32768;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int writeButton (int button, bool pressed)
{
  int retStatus = 0;
  if (button < nButton && nButton >= 0)
    dataButton[button] = (bool) pressed;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int16_t readLastAxisValue (int axis)
{
    return (int16_t) dataAxis[axis] - 32768;
}

bool writeLastButtonState (int button)
{
    return (bool) dataButton[button];
}
