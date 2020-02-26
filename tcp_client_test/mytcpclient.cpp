#include "mytcpclient.h"
#include <QDebug>

myTcpClient::myTcpClient()
{
//    char *data = "hello qt!";
    qDebug() << "init client module";

    const char data[] = "goto 111 hello qt!";
    client = new QTcpSocket(this);
    qDebug() << "connect to host 6665";
    client->connectToHost("127.0.01", 8885);

    qDebug() << "send to 6665";
    client->write(data);

    while (true) {
        client->write(data, strlen(data));
        qDebug() << "write sleep 3";
        QThread::sleep(3);
    }

    client->close();
}
