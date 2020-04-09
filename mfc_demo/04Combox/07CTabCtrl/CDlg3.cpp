// CDlg3.cpp: 实现文件
//

#include "pch.h"
#include "07CTabCtrl.h"
#include "CDlg3.h"
#include "afxdialogex.h"


// CDlg3 对话框

IMPLEMENT_DYNAMIC(CDlg3, CDialogEx)

CDlg3::CDlg3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	//将dlg1 和 dlg2 两个对话框加载到tabctrl标签控件上
	new_tab.AddPage(TEXT("系统消息"), &dlg1, IDD_DIALOG1);
	new_tab.AddPage(TEXT("系统设置"), &dlg2, IDD_DIALOG2);
	new_tab.AddPage(TEXT("测试页面"), &dlg3, IDD_DIALOG3);
	new_tab.Show();

	

}

CDlg3::~CDlg3()
{
}

void CDlg3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, new_tab);
}


BEGIN_MESSAGE_MAP(CDlg3, CDialogEx)
END_MESSAGE_MAP()


// CDlg3 消息处理程序
