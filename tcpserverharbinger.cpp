
#include "tcpserverharbinger.h"

#include <QDebug>

#define DEBUG_TCP 1

TcpServerHarbinger::TcpServerHarbinger(QWidget *parent, int _startPort, int _nConnections)  : QThread(parent)
{
    nConnections = _nConnections;
    startPort = _startPort;

    m_loop = true;
}

TcpServerHarbinger::~TcpServerHarbinger()
{
    stopLoop();
    usleep(200000);
}

void TcpServerHarbinger::run () {

    //* TCP Initialization
    // Create TCP connection for each axis
    for (int i=0; i < nConnections; i++) {
        if (DEBUG_TCP) qDebug() << "TCP Server["<< i <<"]: listening on TCP port: [" << startPort + i << "]";
        vecServer[i] = new TcpServer(startPort + i);
        vecServer[i]->start16();
    }

    //* TCP LOOP
    if (DEBUG_TCP) qDebug() << "Tcp Server Harbinger: Starting Loop";
    while (m_loop)  // Loop -> if  m_loop = true
    {
        for (int i=0; i < nConnections; i++)      // Read data array and send trough TCP
        {
            if(vecServer[i]->newDataAvailable())   // If connection closed, RECONECT
            {
                if (DEBUG_TCP) qDebug() << "TCP Server["<< i <<"]: Reading data on TCP port: [" << startPort + i << "]";
                vecData16[i] = vecServer[i]->readLast16();
            }
        }
        usleep(10000); // Microseconds
    }
    if (DEBUG_TCP) qDebug() << "Tcp Server Harbinger: Loop Terminated";
    /**/


    /* TCP Initialization
    // Create TCP connection for each axis
    for (int i=0; i < nConnections; i++) {
        if (DEBUG_TCP) qDebug() << "TCP Server["<< i <<"]: listening on TCP port: [" << startPort + i << "]";
        vecServer[i] = new TcpServer(address, startPort + i);
    }
    // Initialize Axis to zero
    for (int i=0; i < nConnections; i++) {
        vecServer[i]->send16(32767);   // Initialize to neutral value (= 32767)
        vecData16[i] = 32767;
        vecDataOld[i] = 32767;
    }
    /**/

    /* TCP LOOP
    if (DEBUG_TCP) qDebug() << "Tcp Server Harbinger: Starting Loop";
    while (m_loop)  // Loop -> if  m_loop = true
    {
        for (int i=0; i < nConnections; i++)      // Read data array and send trough TCP
        {
            if(!vecServer[i]->isConnected())   // If connection closed, RECONECT
                    {
                        delete vecServer[i];
                        if (DEBUG_TCP) qDebug() << "TCP Server["<< i <<"]: Re-estabilshing TCP port: ADD: " << address << "[" << startPort + i << "]";
                        vecServer[i] = new TcpServer(address, startPort + i);

                        vecServer[i]->isConnected();
                    }
            else if(vecServer[i] != NULL) {      // Send data
                if(vecData16[i] != vecDataOld[i])   // Don't resend same data
                {
                    if (!m_wait)
                    {
                        vecServer[i]->send16((uint16_t) vecData16[i]);
                        vecDataOld[i] = vecData16[i];
                        if (DEBUG_TCP) qDebug() << "Send data " << i << " : " <<  (int) vecData16[i];
                    }
                }
            }
        }
        usleep(100000); // Microseconds
    }
    if (DEBUG_TCP) qDebug() << "Tcp Server Harbinger: Loop Terminated";
    /**/
}

void TcpServerHarbinger::stopLoop()
{
  m_loop = false;
}

void TcpServerHarbinger::resume()
{
  m_wait = false;
}

void TcpServerHarbinger::suspend()
{
  m_wait = true;
}

/*
int TcpServerHarbinger::writeData16 (int connectionId, int16_t value)
{
  int retStatus = 0;
  if (connectionId < nConnections && connectionId >= 0)
    vecData16[connectionId] = (uint16_t) value + 32768;
  else
    retStatus = -1;

  return retStatus; // return 0 if OK, -1 if problem is encuntered
}

int16_t TcpServerHarbinger::readLastAxisValue (int axis)
{
    return (int16_t) vecData16[axis] - 32768;
}
/**/
