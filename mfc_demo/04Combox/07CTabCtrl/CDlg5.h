#pragma once


// CDlg5 对话框

class CDlg5 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg5)

public:
	CDlg5(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlg5();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
