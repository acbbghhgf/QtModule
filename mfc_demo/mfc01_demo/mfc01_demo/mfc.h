#pragma once
#include <afxwin.h>//MFC需要包含的头文件

class MyApp : public CWinApp
{
public:
	//程序入口
	virtual BOOL InitInstance();
};

//窗口框架类
class MyFrame : public CFrameWnd
{
public:
	MyFrame();//窗口构造函数

	//使用消息映射声明宏
	DECLARE_MESSAGE_MAP();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//鼠标左键按下的处理
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);//键盘声明
	afx_msg void OnPaint();//绘图声明


};