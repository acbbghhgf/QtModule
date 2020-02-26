#ifndef MAIN_H
#define MAIN_H
#include <memory>
#include <queue>
#include <vector>
#include <fstream>
#include <memory>
#include <QDebug>
#include <QThread>
#include "application/drawPic/mainwidget.h"
#include <QApplication>
#include "platform/sys/sys_init.h"
#include "platform/sys/signal_init.h"
#include "platform/sys/thread_queue.h"
#include "platform/base/base.h"



typedef struct main_struct{
    m_widget_t m_data;
    Current_State main_state;
}main_struct_t;


int main_init(main_struct_t &m);

#endif // MAIN_H
