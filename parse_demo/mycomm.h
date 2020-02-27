#pragma once
#ifndef MY_COMM__H
#define MY_COMM__H

#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <conio.h>
#include <tchar.h>

class MyComm {
public:
	MyComm(const wchar_t *FileName = _T("COM1"));
	int SendData(const char* Buf, int DataLen);
	int ReadData(char* Buf, int DataLen);

private:
	int comm_init(const wchar_t *FileName);
	
private:
	bool is_opened;//记录是否打开状态

	HANDLE mCom;//保存设备句柄
};

//test comm C
int comm_test();

//给2号机发送模版信号
int mSendToRecv(MyComm& mcom);


#endif // !MY_COMM__H

