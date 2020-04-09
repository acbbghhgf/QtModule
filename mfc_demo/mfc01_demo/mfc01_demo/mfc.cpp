#include "mfc.h"

MyApp app;//应用程序的对象，有且仅有一个

BOOL MyApp::InitInstance()
{
	//创建窗口
	//MyFrame* frame = new MyFrame;
	m_pMainWnd = new MyFrame;

	//更新显示
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	m_pMainWnd->UpdateWindow();

	//m_pMainWnd = frame;//保存指向应用程序的主窗口的指针

	return TRUE;//返回正常的初始化
}

//消息映射分界宏
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
ON_WM_LBUTTONDOWN()//鼠标左键按下宏
ON_WM_CHAR()//键盘按下消息处理宏
ON_WM_PAINT()//绘图映射入口宏
END_MESSAGE_MAP()

//窗口框架的默认构造函数
MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC WINDOW"));
}

//鼠标左键按下的实现
void MyFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	//MessageBox(buf);

	//MFC使用字符串
	CString str;
	//格式化字符串
	str.Format(TEXT(":::: x = %d, y = %d"), point.x, point.y);
	MessageBox(str);
}
//键盘事件处理实现
void MyFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TCHAR buf[1024];
	wsprintf(buf, TEXT("按下了 %c "), nChar);
	MessageBox(buf);
}
//绘图事件实现
void MyFrame::OnPaint()
{
	CPaintDC dc(this);//画到当前窗口
	
	//画文字
	dc.TextOutW(100, 100, TEXT("hello world!"));

	dc.Ellipse(10, 10, 100, 100);
}
