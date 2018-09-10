#include "tcpclientharbinger.h"

#include <QDebug>

#define DEBUG_TCP 1

TcpClientHarbinger::TcpClientHarbinger(QWidget *parent, const char* _address, int _startPort, int _nConnections)  : QThread(parent)
{
    nConnections = _nConnections;
    startPort = _startPort;
    address = _address;

    m_loop = true;
}

TcpClientHarbinger::~TcpClientHarbinger()
{
    stopLoop();
    usleep(200000);
}

void TcpClientHarbinger::run () {

    // Create TCP connection for each axis
    for (int i=0; i < nConnections; i++) {
        if (DEBUG_TCP) qDebug() << "TCP["<< i <<"]: estabilshing TCP port: [" << startPort + i << "]";
        vecClients[i] = new TcpClient(address, startPort + i);
    }
    // Initialize Axis to zero
    for (int i=0; i < nConnections; i++) {
        vecClients[i]->send16(32767);   // Initialize to neutral value (= 32767)
        vecData16[i] = 32767;
        vecDataOld[i] = 32767;
    }


    //* TCP LOOP *//
    if (DEBUG_TCP) qDebug() << "TcoHarbinger: Starting Loop";
    while (m_loop)  // Loop -> if  m_loop = true
    {
        for (int i=0; i < nConnections; i++)      // Read data array and send trough TCP
        {
            if(!vecClients[i]->isConnected())   // If connection closed, RECONECT
                    {
                        delete vecClients[i];
                        if (DEBUG_TCP) qDebug() << "TCP["<< i <<"]: Reconnecting TCP port: ADD: " << address << "[" << startPort + i << "]";
                        vecClients[i] = new TcpClient(address, startPort + i);

                        vecClients[i]->isConnected();
                    }
            else if(vecClients[i] != NULL) {      // Send data
                if(vecData16[i] != vecDataOld[i])   // Don't resend same data
                {
                    if (!m_wait)
                    {
                        vecClients[i]->send16((uint16_t) vecData16[i]);
                        vecDataOld[i] = vecData16[i];
                        if (DEBUG_TCP) qDebug() << "Send data " << i << " : " <<  (int) vecData16[i];
                    }
                }
            }
        }
        usleep(100000); // Microseconds
    }
    if (DEBUG_TCP) qDebug() << "TcoHarbinger: Loop Terminated";
}

void TcpClientHarbinger::stopLoop()
{
  m_loop = false;
}

void TcpClientHarbinger::resume()
{
  m_wait = false;
}

void TcpClientHarbinger::suspend()
{
  m_wait = true;
}

int TcpClientHarbinger::writeData16 (int connectionId, int16_t value)
{
  int retStatus = 0;
  if (connectionId < nConnections && connectionId >= 0)
    vecData16[connectionId] = (uint16_t) value + 32768;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int16_t TcpClientHarbinger::readLastAxisValue (int axis)
{
    return (int16_t) vecData16[axis] - 32768;
}
