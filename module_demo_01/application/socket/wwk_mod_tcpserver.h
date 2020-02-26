#ifndef WWK_MOD_TCPSERVER_H
#define WWK_MOD_TCPSERVER_H

#include "platform/base/wwk_type.h"
#include <QtNetwork>

void mywin32_tcp();

void myqt_tcp();

class MyQtTcp:public QObject
{
    Q_OBJECT
public:
    MyQtTcp();


public slots:
    void acceptConnection();
    void readClient();

public:
    QTcpServer *server;//服务端
    QTcpSocket *clientConnection;//socket链接
};

#endif // WWK_MOD_TCPSERVER_H
