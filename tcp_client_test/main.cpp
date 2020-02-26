#include "mainwidget.h"

#include <QApplication>
#include "mytcpclient.h"


std::unique_ptr<QApplication> q_app;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    mainWidget w;
//    w.show();
    myTcpClient myclient;
    while(true)
    {
        QThread::sleep(1);
        q_app->processEvents();
    }
    return a.exec();
}
