// CSellDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CSellDlg.h"
#include "CInfoFile.h"


// CSellDlg

IMPLEMENT_DYNCREATE(CSellDlg, CFormView)

CSellDlg::CSellDlg()
	: CFormView(IDD_SELL)
	, m_price(0)
	, m_num(0)
	, m_sellInfo(_T(""))
{

}

CSellDlg::~CSellDlg()
{
}

void CSellDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo);
	DDX_Text(pDX, IDC_EDIT2, m_price);
	DDX_Text(pDX, IDC_EDIT3, m_num);
	DDX_Text(pDX, IDC_EDIT1, m_sellInfo);
}

BEGIN_MESSAGE_MAP(CSellDlg, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSellDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON1, &CSellDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSellDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSellDlg 诊断

#ifdef _DEBUG
void CSellDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSellDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSellDlg 消息处理程序


void CSellDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	CInfoFile file;
	file.ReadDocline();//读取商品信息
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		m_combo.AddString((CString)it->name.c_str());
	}

	file.ls.clear();
	m_combo.SetCurSel(0);
}


void CSellDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, text);//获取当前选择的字符

	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if (text == it->name.c_str())
		{
			m_price = it->price;
			m_num = 0;
			UpdateData(FALSE);//内容更新到显示空间
		}
	}

	file.ls.clear();
	
}


void CSellDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//界面数据更新

	if (m_num == 0)
	{
		MessageBox(TEXT("购买个数不能为0"));
		return;
	}

	CString type;
	//获取当前选择项目
	int index = m_combo.GetCurSel();
	m_combo.GetLBText(index, type);
	CString str;
	str.Format(TEXT("商品:%s \r\n 单价:%d \r\n 总价:%d"), type, m_price, m_num, m_price * m_num);

	m_sellInfo = str;
	UpdateData(FALSE);//更新到控件显示
	MessageBox(str);

	//更新到库存文件
	CInfoFile file;
	file.ReadDocline();
	for (auto it = file.ls.begin(); it != file.ls.end(); ++it)
	{
		if (type == it->name.c_str())
		{
			it->num = it->num - m_num;
		}
	}
	file.WriteDocline();//更新内容
	file.ls.clear();

	m_sellInfo.Empty();//清空
	m_num = 0;
	UpdateData(FALSE);
}


void CSellDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	//取消按钮处理
	m_combo.SetCurSel(0);//选择第一个项目
	m_sellInfo.Empty();
	m_num = 0;
	OnCbnSelchangeCombo1();
}
