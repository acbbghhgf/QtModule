#pragma once

#include <list>
#include <fstream>
#include <iostream>
#include <string>
#include "pch.h"

#define _F_LOGIN "./login.ini"
#define _F_STOCK "./stock.txt"

struct msg
{
	int id;
	std::string name;
	int price;
	int num;
};

class CInfoFile
{
public:
	CInfoFile();
	~CInfoFile();

	//读取登录信息
	void ReadLogin(CString& name, CString& pwd);

	//修改密码
	void WritePwd(char* name, char* pwd);

	//读取商品数据
	void ReadDocline();

	//商品写入文件
	void WriteDocline();

	//添加新商品
	void AddLine(CString name, int num, int price);

	std::list<msg> ls; //存储商品容器
	int num; //记录商品个数
};

