#pragma once


// CDlg4 对话框

class CDlg4 : public CDialogEx
{
	DECLARE_DYNAMIC(CDlg4)

public:
	CDlg4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlg4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
