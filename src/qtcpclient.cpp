#include "qtcpclient.h"

QTcpClient::QTcpClient (QObject *parent) : QObject (parent)
{

}

void QTcpClient::connect (const char* address, int port)
{
  qDebug() << "Connecting...";
}
