/*
 * @Description:
 * @Author: kai
 * @Date: 2019-09-30 16:28:30
 * @LastEditors: kai
 * @LastEditTime: 2019-10-12 11:25:18
 */

#include "platform/base/base.h"
#include "signal_init.h"

int mi_signal_init()
{
#ifdef Q_WS_WIN32
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigaddset(&s, SIGSTOP);
    sigaddset(&s, SIGTERM);
    sigaddset(&s, SIGKILL);
    sigaddset(&s, SIGTSTP);
    sigaddset(&s, SIGPIPE);

    if(sigprocmask(SIG_BLOCK,&s,NULL) == -1)
    {
        return -1;
    }
#else
#endif
    return 0;
}
