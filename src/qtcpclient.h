#ifndef QTCPCLIENT_H
#define QTCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class QTcpClient : public QObject
{
  Q_OBJECT

public:
  explicit QTcpClient (QObject *parent = 0);
  void connect(const char* address, int port);

Q_SIGNALS:

public Q_SLOTS:

private:

};

#endif // QTCPCLIENT_H
