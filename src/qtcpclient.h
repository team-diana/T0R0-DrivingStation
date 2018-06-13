#ifndef QTCPCLIENT_H
#define QTCPCLIENT_H

#include <QObject>
#include <QDebug>

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

class Client : public QObject
{
  Q_OBJECT

public:
  Client (QObject *parent = 0, const char* address = "127.0.0.1", int port = 8088);
  ~Client();
  void send8(uint8_t data);
  void send16(uint16_t data);
  bool isConnected();

Q_SIGNALS:

public Q_SLOTS:

private:
  int sock;
  int port;
  char address[16];

  bool connected;
};

#endif // QTCPCLIENT_H
