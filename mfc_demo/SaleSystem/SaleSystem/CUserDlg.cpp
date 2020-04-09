// CUserDlg.cpp: 实现文件
//

#include "pch.h"
#include "SaleSystem.h"
#include "CUserDlg.h"
#include "CInfoFile.h"


// CUserDlg

IMPLEMENT_DYNCREATE(CUserDlg, CFormView)

CUserDlg::CUserDlg()
	: CFormView(IDD_USER)
	, m_user(_T(""))
	, m_name(_T(""))
	, m_newPwd(_T(""))
	, m_surePwd(_T(""))
{

}

CUserDlg::~CUserDlg()
{
}

void CUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_name);
	DDX_Text(pDX, IDC_EDIT3, m_newPwd);
	DDX_Text(pDX, IDC_EDIT4, m_surePwd);
}

BEGIN_MESSAGE_MAP(CUserDlg, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CUserDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CUserDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CUserDlg 诊断

#ifdef _DEBUG
void CUserDlg::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CUserDlg::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CUserDlg 消息处理程序
void CUserDlg::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	//初始化代码
	m_user = TEXT("销售员");
	CInfoFile file;
	CString name, pwd;
	file.ReadDocline();
	file.ReadLogin(name, pwd);
	m_name = name;

	UpdateData(FALSE);

	// TODO: 在此添加专用代码和/或调用基类
}


void CUserDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_newPwd.IsEmpty() || m_surePwd.IsEmpty())
	{
		MessageBox(TEXT("输入的内容不能为空"));
		return;
	}

	//密码不一致
	if (m_newPwd != m_surePwd)
	{
		MessageBox(TEXT("新密码与确定密码不一致"));
		return;
	}
	CInfoFile file;
	CString name, pwd;
	file.ReadLogin(name, pwd);

	//新密码与原密码要不一致
	if (m_newPwd == pwd)
	{
		MessageBox(TEXT("新密码与原密码重复！"));
		return;
	}

	//修改密码
	CStringA tmpName;
	CStringA tmpPwd;
	tmpName = name;
	tmpPwd = m_newPwd;

	file.WritePwd(tmpName.GetBuffer(), tmpPwd.GetBuffer());
	MessageBox(TEXT("修改密码成功"));

	//清空输入内容
	m_newPwd.Empty();
	m_surePwd.Empty();
	UpdateData(FALSE);
}


void CUserDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	m_surePwd.Empty();
	m_newPwd.Empty();
	UpdateData(FALSE);
}
