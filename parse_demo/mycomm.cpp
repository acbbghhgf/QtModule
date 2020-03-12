#include "mycomm.h"


int comm_test()
{
    HANDLE hCom;
    hCom = CreateFile(_T("COM1"),//COM2口
        GENERIC_READ | GENERIC_WRITE,//允许读和写
        0,//独占方式
        NULL,
        OPEN_EXISTING,//打开而不是创建
        0,//同步方式
        NULL);
    if (hCom == (HANDLE)-1)
    {
        printf("打开COM失败!\n");
        return FALSE;
    }
    else
    {
        printf("COM打开成功！\n");
    }
    if (!SetupComm(hCom, 1024, 1024))//输入缓冲区和输出缓冲区的大小都是1024
    {
        printf("error id = %d\n", GetLastError());
    }

    COMMTIMEOUTS TimeOuts;//设定读超时    
    TimeOuts.ReadIntervalTimeout = MAXWORD;//把间隔超时设置为最大，总超时设置为0将导致readfile立即返回并完成操作。
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//读时间系数
    TimeOuts.ReadTotalTimeoutConstant = 0;//读时间常量
    TimeOuts.WriteTotalTimeoutMultiplier = 50;//设定写超时,总超时=时间系数*要求读/写的字符数 + 时间常量
    TimeOuts.WriteTotalTimeoutConstant = 2000;//设置写超时
    SetCommTimeouts(hCom, &TimeOuts);//设置超时

    DCB dcb1;
    //获取串行口的配置。
    GetCommState(hCom, &dcb1);
    dcb1.BaudRate = 115200;//波特率为9600
    dcb1.ByteSize = 8;//每个字节有8位
    dcb1.Parity = NOPARITY;//无奇偶校验位
    dcb1.StopBits = TWOSTOPBITS;//两个停止位
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    //设置串行口的配置
    SetCommState(hCom, &dcb1);

    DWORD wCount = 256;//读取的字节数
    DWORD wCount1;
    char mbuf[] = "hello world!\n";

    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空缓冲区
    while (1)
    {
        int i = 0;
        FILE* fp1;
        unsigned char str[256];
        //str-保存数据缓冲区,wCount-读取字节个数，wCount1-实际读取的字节数的指针
        //读串口
#if 0
        if (!ReadFile(hCom, str, wCount, &wCount1, NULL))
        {
            printf("读串口失败!");
            return FALSE;
        }

        //保存本地文件中。
        //fp1 = fopen("串口发送的数.txt", "a+");
        //if (wCount1 > 0)
        //{
        //    printf("wCount1:%d\n", wCount1);
        //}
        printf("读串口成功!读取数据为:\n");
        for (i = 0; i < wCount1; i++)
        {
            printf("%02X ", str[i]);
            //fprintf(fp1, "%02X ", str[i]);
        }
        printf("\n");
#endif
        if (!WriteFile(hCom, mbuf, strlen(mbuf), &wCount1, NULL))
        {
            printf("write comm fail!\n");
        }
        else
        {
            printf("send hello world comm success\n");
        }
        //fclose(fp1);
    }

    CloseHandle(hCom);

    std::cout << "Hello World!\n";

    return 0;
}

//初始化串口设备，为后面调用读取或者发送数据提供接口
MyComm::MyComm(const wchar_t* FileName)
{
    if (comm_init(FileName) != 0)
    {
        is_opened = false;
    }
    else
    {
        is_opened = true;
    }
}

//内部初始化函数，打卡串口设备并初始化
//成功返回0，失败返回-1
int MyComm::comm_init(const wchar_t* FileName)
{
    mCom = CreateFile(_T("COM9"),//COM2口
        GENERIC_READ | GENERIC_WRITE,//允许读和写
        0,//独占方式
        NULL,
        OPEN_EXISTING,//打开而不是创建
        0,//同步方式
        NULL);
    //mCom = CreateFile(FileName,//COM2口
    //    GENERIC_READ | GENERIC_WRITE,//允许读和写
    //    0,//独占方式
    //    NULL,
    //    OPEN_EXISTING,//打开而不是创建
    //    0,//同步方式
    //    NULL);
    if (mCom == (HANDLE)-1)
    {
        printf("打开COM失败!\n");
        return -1;
    }
    else
    {
        printf("COM打开成功！\n");
    }
    if (!SetupComm(mCom, 0, 0))//输入缓冲区和输出缓冲区的大小都是1024
    {
        printf("error id = %d\n", GetLastError());
        return -1;
    }

    COMMTIMEOUTS TimeOuts;//设定读超时    
    TimeOuts.ReadIntervalTimeout = MAXWORD;//把间隔超时设置为最大，总超时设置为0将导致readfile立即返回并完成操作。
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//读时间系数
    TimeOuts.ReadTotalTimeoutConstant = 0;//读时间常量
    TimeOuts.WriteTotalTimeoutMultiplier = 50;//设定写超时,总超时=时间系数*要求读/写的字符数 + 时间常量
    TimeOuts.WriteTotalTimeoutConstant = 2000;//设置写超时
    SetCommTimeouts(mCom, &TimeOuts);//设置超时

    DCB dcb1;
    //获取串行口的配置。
    GetCommState(mCom, &dcb1);
    dcb1.BaudRate = 9600;//波特率为9600
    dcb1.ByteSize = 8;//每个字节有8位
    dcb1.Parity = NOPARITY;//无奇偶校验位
    dcb1.StopBits = TWOSTOPBITS;//两个停止位
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    //设置串行口的配置
    SetCommState(mCom, &dcb1);

    return 0;
}

//发送串口数据，成功返回发送数据的长度，失败返回-1
int MyComm::SendData(const char* Buf, int DataLen)
{
    DWORD wCount1;
    if (!is_opened)
    {
        printf("%s:%d : comm open fail\n", __func__, __LINE__);
        return -1;
    }
    if (!WriteFile(mCom, Buf, DataLen, &wCount1, NULL))
    {
        printf("%s:%d : comm send data fail\n", __func__, __LINE__);
        return -1;
    }

    printf("%s:%d : send data success, data len : %d\n", __func__, __LINE__, wCount1);
    return wCount1;
}

//读取串口设备数据。
//【out】Buf--读取存储缓冲区指针，【in】DataLen--读取长度
//成功返回读取实际长度，失败返回-1
int MyComm::ReadData(char* Buf, int DataLen)
{
    DWORD wCount = 256;//读取的字节数
    DWORD InfactCount = 0;
    DWORD wCount1;
    if (!is_opened)
    {
        printf("%s:%d : comm open fail\n", __func__, __LINE__);
        return -1;
    }
    if (DataLen > wCount)
    {
        while (DataLen > wCount)
        {
            
            if (!ReadFile(mCom, Buf, wCount, &wCount1, NULL))
            {
                printf("%s:%d : comm read data fail\n", __func__, __LINE__);
                if (InfactCount == 0)
                {
                    printf("%s:%d : comm read data fail\n", __func__, __LINE__);
                    return -1;
                }
                else
                {
                    printf("%s:%d : Infact send len : %d, need send len : %d\n", __func__, __LINE__, InfactCount, DataLen);
                    break;
                }
            }
            DataLen -= wCount;
            Buf += wCount1;
            InfactCount += wCount1;
        }
        if (DataLen > 0)
        {
            if (!ReadFile(mCom, Buf, DataLen, &wCount1, NULL))
            {
                printf("%s:%d : comm read data fail\n", __func__, __LINE__);
            }
            else
            {
                InfactCount += wCount1;
            }
        }
    }
    else
    {
        if (!ReadFile(mCom, Buf, DataLen, &wCount1, NULL))
        {
            printf("%s:%d : comm read data fail\n", __func__, __LINE__);
            return -1;
        }
        printf("%s:%d : rend data success, data len : %d\n", __func__, __LINE__, wCount1);
        InfactCount = wCount1;
    }
    return InfactCount;
}


int mSendToRecv(MyComm &mcom)
{
    char BCA[] = "BCA";
    char bca[] = "bca";

    //1.1发送信号
    //发送BCDA
    if (mcom.SendData(BCA, strlen(BCA)) == -1)
    {
        return -1;
    }
    //sleep
    Sleep(500);
    //发送bcda
    if (mcom.SendData(bca, strlen(bca)) == -1)
    {
        return -1;
    }

    return 0;
}
