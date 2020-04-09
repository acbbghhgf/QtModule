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

	//��ȡ��¼��Ϣ
	void ReadLogin(CString& name, CString& pwd);

	//�޸�����
	void WritePwd(char* name, char* pwd);

	//��ȡ��Ʒ����
	void ReadDocline();

	//��Ʒд���ļ�
	void WriteDocline();

	//�������Ʒ
	void AddLine(CString name, int num, int price);

	std::list<msg> ls; //�洢��Ʒ����
	int num; //��¼��Ʒ����
};

