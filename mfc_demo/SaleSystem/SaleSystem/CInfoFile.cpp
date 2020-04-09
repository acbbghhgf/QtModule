#include "pch.h"
#include "CInfoFile.h"

CInfoFile::CInfoFile()
{
}

CInfoFile::~CInfoFile()
{
}

void CInfoFile::ReadLogin(CString& name, CString& pwd)
{
	std::ifstream ifs;//�����ļ��������
	ifs.open(_F_LOGIN);//���ļ�

	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));//��ȡ��һ��
	name = CString(buf);//char * תΪCString
	
	memset(buf, 0, sizeof(buf));//���buf
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();//�ر��ļ�

}

void CInfoFile::WritePwd(char* name, char* pwd)
{
	std::ofstream ofs;//�����ļ��������
	ofs.open(_F_LOGIN);//���ļ�

	ofs << name << std::endl;//��nameд���ļ�������
	ofs << pwd << std::endl;//��pwdд���ļ�������

	ofs.close();//�ر��ļ�

}

void CInfoFile::ReadDocline()
{
	std::ifstream ifs(_F_STOCK);//���뷽ʽ���ļ�

	char buf[1024] = { 0 };
	num = 0;//��ʼ����Ʒ��Ŀ
	ls.clear();//��ʼ������
	//ȡ����ͷ
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())//ѭ��ִ�е��ļ���β
	{
		msg tmp;//�����ݴ����
		
		ifs.getline(buf, sizeof(buf));
		num++;

		char* set = strtok(buf, "|");//��|Ϊ�ָ����и��ַ���
		if (set != NULL)
		{
			tmp.id = std::atoi(set);//��һ��Ϊ��Ʒid
		}
		else
		{
			break;//�Ҳ����ָ���������ѭ��
		}

		set = strtok(NULL, "|");
		tmp.name = set;//��Ʒ����

		set = strtok(NULL, "|");
		tmp.price = std::atoi(set);//��Ʒ�۸�

		set = strtok(NULL, "|");
		tmp.num = std::atoi(set);//��Ʒ��Ŀ

		ls.push_back(tmp);
	}

	ifs.close();//�ر��ļ�
}

void CInfoFile::WriteDocline()
{
	std::ofstream ofs(_F_STOCK);//�����ʽ���ļ�
	if (ls.size() > 0)
	{
		ofs << "��ƷID|��Ʒ����|��Ʒ�۸�|���" << std::endl;//д���ͷ
		//ͨ��������д������
		for (auto it = ls.begin(); it != ls.end(); ++it)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << std::endl;
		}
	}
	ofs.close();//�ر��ļ�
}

void CInfoFile::AddLine(CString name, int num, int price)
{
	msg tmp;
	if (ls.size() > 0)
	{
		if (!name.IsEmpty() && num > 0 && price > 0)
		{
			tmp.id = ls.size() + 1;
			CStringA str;
			str = name;
			tmp.name = str.GetBuffer();
			tmp.num = num;
			tmp.price = price;

			ls.push_back(tmp);//���������
		}
	}
}
