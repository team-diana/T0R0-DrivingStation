#include "tcpharbinger.h"

#include <QDebug>



TcpHarbinger::TcpHarbinger(QWidget *parent, const char* address, int _startPortAxis, int _nAxis, int _startPortButton, int _nButton)  : QWidget(parent)
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

void TcpHarbinger::run () {

    qDebug() << "TcoHarbinger: Starting tcpLoop";

  while (m_loop)  // Loop -> if  m_loop = true
  {
    for (int i=0; i < nAxis; i++) {     // Read data array and send trough TCP
        qDebug() << "dataAxis[" << i << "]: " << dataAxis[i];
        clientAxis[i]->send16(dataAxis[i]);
    }
    usleep(100000); // Microseconds
  }
  qDebug() << "TcoHarbinger: TcpLoop Terminated";
}

void TcpHarbinger::stop()
{
  m_loop = false;
}

int TcpHarbinger::writeAxis (int axis, int16_t value)
{
  int retStatus = 0;
  if (axis < nAxis && axis >= 0)
    dataAxis[axis] = (uint16_t) value + 32768;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int TcpHarbinger::writeButton (int button, bool pressed)
{
  int retStatus = 0;
  if (button < nButton && nButton >= 0)
    dataButton[button] = (bool) pressed;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int16_t TcpHarbinger::readLastAxisValue (int axis)
{
    return (int16_t) dataAxis[axis] - 32768;
}

bool TcpHarbinger::writeLastButtonState (int button)
{
    return (bool) dataButton[button];
}
