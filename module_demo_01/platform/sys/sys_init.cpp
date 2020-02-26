/*
 * @Description:
 * @Author: kai
 * @Date: 2019-10-12 10:23:20
 * @LastEditors: kai
 * @LastEditTime: 2019-10-17 14:34:42
 */
#include "sys_init.h"
#include <QDebug>
#include "signal_init.h"
#include "application/main/main.h"

extern main_struct_t main_body;


int system_init()
{
    int ret = mi_signal_init();
    if (ret < 0)
    {
        qDebug() << "signal init error";
        exit(-1);
    }

    ret = threads_init();
    if (!ret)
    {
        qDebug() << "threads init over";
    }

    return 0;
}

int threads_init()
{
    std::string cur_role;

    pthread_attr_t t_attr;
    pthread_attr_init(&t_attr);
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

    //这里启动2号机的线程
    pthread_t readData, drawData, displayPic;
    int ret = 0;

//    ret = pthread_create(&readData, &t_attr, reinterpret_cast<void *(*)(void *)>(data_read_thread), (void *)&main_body.data_read_body);
//    if (ret)
//    {
//        qDebug() << "create [data_read_thread] failed!!!";
//        exit(-1);
//    }


//    pthread_attr_destroy(&t_attr);

    return 0;
}
