
// 03EditCtrlDlg.h: 头文件
//

#pragma once


// CMy03EditCtrlDlg 对话框
class CMy03EditCtrlDlg : public CDialogEx
{
// 构造
public:
	CMy03EditCtrlDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY03EDITCTRL_DIALOG };
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
	CEdit Edit1;
	CEdit Edit2;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
private:
	CString m_edit3;
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
