#ifndef QTCPCLIENT_H
#define QTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QByteArray>

class Client : public QObject
{
  Q_OBJECT

public:
  explicit Client (QObject *parent = 0);
  bool connect(const char* address, int port);
  bool writeData(QByteArray data);
  //QByteArray IntToArray(qint32 source);

Q_SIGNALS:

public Q_SLOTS:

private:
  QTcpSocket *socket;
};

#endif // QTCPCLIENT_H
