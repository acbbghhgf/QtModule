#include "mycomm.h"

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include "tchar.h"


int comm_test()
{
    HANDLE hCom;
    hCom = CreateFile(_T("COM2"),//COM2口
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
    SetupComm(hCom, 20480, 20480);//输入缓冲区和输出缓冲区的大小都是1024

    COMMTIMEOUTS TimeOuts;//设定读超时    
    TimeOuts.ReadIntervalTimeout = 100;
    TimeOuts.ReadTotalTimeoutMultiplier = 500;
    TimeOuts.ReadTotalTimeoutConstant = 5000;
    TimeOuts.WriteTotalTimeoutMultiplier = 500;//设定写超时
    TimeOuts.WriteTotalTimeoutConstant = 2000;
    SetCommTimeouts(hCom, &TimeOuts);//设置超时

    DCB dcb1;
    GetCommState(hCom, &dcb1);
    dcb1.BaudRate = 115200;//波特率为9600
    dcb1.ByteSize = 8;//每个字节有8位
    dcb1.Parity = NOPARITY;//无奇偶校验位
    dcb1.StopBits = TWOSTOPBITS;//两个停止位
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    SetCommState(hCom, &dcb1);
    DWORD wCount = 256;//读取的字节数
    DWORD wCount1;
    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//清空缓冲区
    while (1)
    {
        int i = 0;
        FILE* fp1;
        unsigned char str[256];
        if (!ReadFile(hCom, str, wCount, &wCount1, NULL))
        {
            printf("读串口失败!");
            return FALSE;
        }
        fp1 = fopen("串口发送的数.txt", "a+");
        if (wCount1 > 0)
        {
            printf("wCount1:%d\n", wCount1);
        }
        printf("读串口成功!读取数据为:\n");
        for (i = 0; i < wCount1; i++)
        {
            printf("%02X ", str[i]);
            fprintf(fp1, "%02X ", str[i]);
        }
        printf("\n");
        fclose(fp1);
    }

    CloseHandle(hCom);

    std::cout << "Hello World!\n";

    return 0;
}