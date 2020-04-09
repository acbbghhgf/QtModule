// CDelDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CDelDlg.h"
#include "CInfoFile.h"


// CDelDlg

IMPLEMENT_DYNCREATE(CDelDlg, CFormView)

CDelDlg::CDelDlg()
	: CFormView(IDD_DEL)
	, m_price(0)
	, m_num(0)
{

}

CDelDlg::~CDelDlg()
{
}

void CDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT1, m_price);
	DDX_Text(pDX, IDC_EDIT2, m_num);
}

BEGIN_MESSAGE_MAP(CDelDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDelDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDelDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDelDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDelDlg 诊断

#ifdef _DEBUG
void CDelDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CDelDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDelDlg 消息处理程序


void CDelDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	m_combo.SetCurSel(0);
}


void CDelDlg::OnCbnSelchangeCombo1()
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
			m_price = it->price;
			m_num = 0;
			UpdateData(FALSE);
		}
	}
}


void CDelDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//确定按钮实现
	UpdateData(TRUE);
	if (m_num == 0)
	{
		MessageBox(TEXT("个数不能为0!"));
		return;
	}

	CString type;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);
	CString str;
	str.Format(TEXT("删除商品：%s \r\n 单价：%d \r\n 个数：%d"), type, m_price, m_num);
	MessageBox(str);

	CInfoFile file;
	file.ReadDocline();

	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if (type == it->name.c_str())
		{
			it->num = it->num - m_num;
		}
	}
	file.WriteDocline();//更新数据内容
	file.ls.clear();

	m_num = 0;
	UpdateData(FALSE);//更新显示控件
}


void CDelDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消按钮实现
	m_combo.SetCurSel(0);
	m_num = 0;
	OnCbnSelchangeCombo1();
}
