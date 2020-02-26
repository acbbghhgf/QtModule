#include "application/drawPic/mainwidget.h"
#include "main.h"
#include <QApplication>
#include "application/socket/wwk_mod_tcpserver.h"

std::unique_ptr<QApplication> q_app;
std::unique_ptr<mainWidget> w;

int main(int argc, char *argv[])
{
    q_app.reset(new QApplication(argc, argv));
//    w.reset(new mainWidget);
    qDebug() << "system is booting";

    MyQtTcp mytcpserver;

    while(true)
    {
        QThread::sleep(1);
        q_app->processEvents();
    }
    return q_app->exec();
}
