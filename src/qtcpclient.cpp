#include "qtcpclient.h"

Client::Client (QObject *parent) : QObject (parent)
{

}

bool Client::connect (const char* address, int port)
{
  qDebug() << "Connecting to " << address << " on port " << port;

  // Connect to TCP Host (or server)
  socket = new QTcpSocket(this);
  socket->connectToHost(address, port);
  return socket->waitForConnected();
}

bool Client::writeData(QByteArray data)
{
    if(socket->state() == QAbstractSocket::ConnectedState)
    {
        qDebug() << "Writing data to TCP " << data;
        socket->write(IntToArray(data.size())); //write size of data
        socket->write(data); //write the data itself
        return socket->waitForBytesWritten();
    }
    else
        return false;
}

QByteArray Client::IntToArray(qint32 source) //Use qint32 to ensure that the number have 4 bytes
{
    //Avoid use of cast, this is the Qt way to serialize objects
    QByteArray temp;
    QDataStream data (&temp, QIODevice::ReadWrite);
    data << source;
    return temp;
}

// Part of the code is based on https://www.youtube.com/watch?v=u5OdR46542M
// and on https://stackoverflow.com/questions/20546750/qtcpsocket-reading-and-writing
