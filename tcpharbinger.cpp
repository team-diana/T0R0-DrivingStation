#include "tcpharbinger.h"

#include <QDebug>



TcpHarbinger::TcpHarbinger(QWidget *parent, const char* address, int _startPort, int _nConnections)  : QObject(parent)
{
    nConnections = _nConnections;
    startPort = _startPort;

    m_loop = true;

    // Create TCP connection for each axis
    for (int i=0; i < nConnections; i++) {
        qDebug() << "Axis["<< i <<"]: estabilshed TCP port: ["<< startPort + i << "]";
        vecClients[i] = new TcpClient(address, startPort + i);
    }
    // Initialize Axis to zero
    for (int i=0; i < nConnections; i++) {
        vecClients[i]->send16(32767);   // Initialize to neutral value (= 32767)
        vecData16[i] = 32767;
    }

}

TcpHarbinger::~TcpHarbinger()
{
    stopLoop();
    usleep(200000);
}

void TcpHarbinger::startLoop () {

    qDebug() << "TcoHarbinger: Starting Loop";

  while (m_loop)  // Loop -> if  m_loop = true
  {
    for (int i=0; i < nConnections; i++)      // Read data array and send trough TCP
    {
        qDebug() << "vecData16[" << i << "]: " << vecData16[i];

        if (!m_wait)
            vecClients[i]->send16((uint16_t) vecData16[i]);
    }
    usleep(1000000); // Microseconds
  }
  qDebug() << "TcoHarbinger: Loop Terminated";
}

void TcpHarbinger::stopLoop()
{
  m_loop = false;
}

void TcpHarbinger::resume()
{
  m_wait = false;
}

void TcpHarbinger::suspend()
{
  m_wait = true;
}

int TcpHarbinger::writeAxis (int axis, int16_t value)
{
  int retStatus = 0;
  if (axis < nConnections && axis >= 0)
    vecData16[axis] = (uint16_t) value + 32768;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int16_t TcpHarbinger::readLastAxisValue (int axis)
{
    return (int16_t) vecData16[axis] - 32768;
}
