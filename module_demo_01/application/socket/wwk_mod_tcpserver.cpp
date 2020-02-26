#include "wwk_mod_tcpserver.h"

#if 0 //尝试在win32下的C编程TCP socket。
void mywin32_tcp()
{
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0)
    {
        printf("WSAStartup error\n");
        return ;
    }

    if(LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
    {
        WSACleanup();
        printf("%s:%d,error\n", __func__, __LINE__);
        return ;
    }

    SOCKET sockSrv = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addrSrv;
    addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6000);

    bind(sockSrv, (SOCKADDR *)&addrSrv, sizeof(SOCKADDR));//绑定端口

    listen(sockSrv, 5);

    SOCKADDR_IN addrClient;//存储客户端IP地址信息
    int len = sizeof(SOCKADDR);

    while(1)
    {
        SOCKET sockConn = accept(sockSrv, (SOCKADDR *)&addrClient, &len);
        char sendBuf[50];
        sprintf(sendBuf, "Welcome %s to here!", inet_ntoa(addrClient.sin_addr));
        send(sockConn, sendBuf, strlen(sendBuf)+1, 0);//发送消息到客户端
        char recvBuf[50];
        recv(sockConn, recvBuf, 50, 0);//接收客户端消息
        printf("%s:%d: %s\n", __func__, __LINE__, recvBuf);

        closesocket(sockConn);//断开链接
    }

}
#endif


//以下采用qt自带的socket编程
void MyQtTcp::acceptConnection()
{
    qDebug() << "accept connect";
    clientConnection = server->nextPendingConnection();
    connect(clientConnection, SIGNAL(readyRead()), this, SLOT(readClient()));

}

void MyQtTcp::readClient()
{
    qDebug() << "read Client";
    QString str = clientConnection->readAll();
    char buf[1024] = {0};
    clientConnection->read(buf, 10);
//    QByteArray dataread = clientConnection->readAll();
    qDebug() << "recv data success before.";
    qDebug() << buf;
//    qDebug() << sizeof(dataread);
//    qDebug() << dataread;
//    qDebug() << str;
    qDebug() << "recv data success after.";

    printf("%s:%d recv data : %s\n", __func__, __LINE__, buf);
}

MyQtTcp::MyQtTcp()
{
    qDebug() << "init myqt tcp server";
    server = new QTcpServer();
    server->listen(QHostAddress::Any, 8885);
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}
