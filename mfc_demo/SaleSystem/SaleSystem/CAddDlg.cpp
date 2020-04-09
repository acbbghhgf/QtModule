// CAddDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CAddDlg.h"
#include "CInfoFile.h"

// CAddDlg

IMPLEMENT_DYNCREATE(CAddDlg, CFormView)

CAddDlg::CAddDlg()
	: CFormView(IDD_ADD)
	, m_price1(0)
	, m_num1(0)
	, m_name2(_T(""))
	, m_price2(0)
	, m_num2(0)
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT5, m_price1);
	DDX_Text(pDX, IDC_EDIT4, m_num1);
	DDX_Text(pDX, IDC_EDIT1, m_name2);
	DDX_Text(pDX, IDC_EDIT2, m_price2);
	DDX_Text(pDX, IDC_EDIT3, m_num2);
}

BEGIN_MESSAGE_MAP(CAddDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAddDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAddDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAddDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAddDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CAddDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CAddDlg 诊断

#ifdef _DEBUG
void CAddDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CAddDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CAddDlg 消息处理程序


void CAddDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	//读取文件数据
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear();

	m_combo.SetCurSel(0);
}


void CAddDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, text);

	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if (text == it->name.c_str())
		{
			m_price1 = it->price;
			m_num1 = 0;
			UpdateData(FALSE);//内容更新到空间
		}
	}
	file.ls.clear();
}


void CAddDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_num1 == 0)
	{
		MessageBox(TEXT("个数不能为0"));
		return;
	}

	CString type;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);

	CString str;
	str.Format(TEXT("添加了商品：%s \r\n 单价：%d \r\n 个数：%d"), type, m_price1, m_num1);
	MessageBox(str);

	//更新到数据文件中
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if (type == it->name.c_str())
		{
			it->num += m_num1;
		}
	}
	file.WriteDocline();//更新内容

	file.ls.clear();
	m_num1 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加个数取消按键
	m_combo.SetCurSel(0);
	m_num1 = 0;
	OnCbnSelchangeCombo1();
}


void CAddDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码\
	//添加新商品确定按钮
	UpdateData(TRUE);

	if (m_num2 <= 0 || m_price2 <= 0 || m_name2.IsEmpty())
	{
		MessageBox(TEXT("输入信息有误"));
		return;
	}

	CInfoFile file;
	file.ReadDocline();
	file.AddLine(m_name2, m_num2, m_price2);
	file.WriteDocline();
	file.ls.clear();
	MessageBox(TEXT("添加成功!"));

	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}


void CAddDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	//添加新商品取消按钮
	m_name2.Empty();
	m_num2 = 0;
	m_price2 = 0;
	UpdateData(FALSE);
}
