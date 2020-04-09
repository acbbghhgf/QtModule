
// 07CTabCtrlDlg.h: 头文件
//

#pragma once
#include "TabSheet.h"
#include "CDlg1.h"
#include "CDlg2.h"
#include "CDlg3.h"
#include "CDlg4.h"
#include "CDlg5.h"

// CMy07CTabCtrlDlg 对话框
class CMy07CTabCtrlDlg : public CDialogEx
{
// 构造
public:
	CMy07CTabCtrlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY07CTABCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CTabSheet m_tab;
	CDlg1 dlg1;
	CDlg2 dlg2;
	
	CDlg3 dlg3;
	CDlg4 dlg4;
	CDlg5 dlg5;
};
