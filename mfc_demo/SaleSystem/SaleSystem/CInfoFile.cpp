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
	std::ifstream ifs;//创建文件输入对象
	ifs.open(_F_LOGIN);//打开文件

	char buf[1024] = { 0 };
	ifs.getline(buf, sizeof(buf));//读取第一行
	name = CString(buf);//char * 转为CString
	
	memset(buf, 0, sizeof(buf));//清空buf
	ifs.getline(buf, sizeof(buf));
	pwd = CString(buf);

	ifs.close();//关闭文件

}

void CInfoFile::WritePwd(char* name, char* pwd)
{
	std::ofstream ofs;//创建文件输出对象
	ofs.open(_F_LOGIN);//打开文件

	ofs << name << std::endl;//将name写入文件并换行
	ofs << pwd << std::endl;//将pwd写入文件并换行

	ofs.close();//关闭文件

}

void CInfoFile::ReadDocline()
{
	std::ifstream ifs(_F_STOCK);//输入方式打开文件

	char buf[1024] = { 0 };
	num = 0;//初始化商品数目
	ls.clear();//初始化容器
	//取出表头
	ifs.getline(buf, sizeof(buf));

	while (!ifs.eof())//循环执行到文件结尾
	{
		msg tmp;//声明暂存变量
		
		ifs.getline(buf, sizeof(buf));
		num++;

		char* set = strtok(buf, "|");//以|为分隔符切割字符串
		if (set != NULL)
		{
			tmp.id = std::atoi(set);//第一个为商品id
		}
		else
		{
			break;//找不到分隔符则跳出循环
		}

		set = strtok(NULL, "|");
		tmp.name = set;//商品名称

		set = strtok(NULL, "|");
		tmp.price = std::atoi(set);//商品价格

		set = strtok(NULL, "|");
		tmp.num = std::atoi(set);//商品数目

		ls.push_back(tmp);
	}

	ifs.close();//关闭文件
}

void CInfoFile::WriteDocline()
{
	std::ofstream ofs(_F_STOCK);//输出方式打开文件
	if (ls.size() > 0)
	{
		ofs << "商品ID|商品名称|商品价格|库存" << std::endl;//写入表头
		//通过迭代器写入内容
		for (auto it = ls.begin(); it != ls.end(); ++it)
		{
			ofs << it->id << "|";
			ofs << it->name << "|";
			ofs << it->price << "|";
			ofs << it->num << std::endl;
		}
	}
	ofs.close();//关闭文件
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

			ls.push_back(tmp);//放在链表后
		}
	}
}
