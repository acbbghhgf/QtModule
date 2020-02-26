#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QObject>
#include <QtNetwork>

class myTcpClient : public QObject
{
    Q_OBJECT
public:
    myTcpClient();

public:
    QTcpSocket *client;

};

#endif // MYTCPCLIENT_H
