#ifndef BASE_H
#define BASE_H

//#ifdef __cplusplus
//extern "C"
//{
//#endif

//#include <errno.h>
//#include <fcntl.h>
//#include <math.h>
//#include <pthread.h>
//#include <signal.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include <sys/types.h>
//#include <time.h>
//#include <unistd.h>



//    enum Current_State{
//        SEND_READY,
//        SENDING,
//        STANDBY
//    };


//#ifdef __cplusplus
//}
//#endif


enum Current_State{
    SEND_READY,
    SENDING,
    STANDBY,
};
#endif // BASE_H
