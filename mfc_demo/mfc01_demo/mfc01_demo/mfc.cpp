#include "mfc.h"

MyApp app;//Ӧ�ó���Ķ������ҽ���һ��

BOOL MyApp::InitInstance()
{
	//��������
	//MyFrame* frame = new MyFrame;
	m_pMainWnd = new MyFrame;

	//������ʾ
	m_pMainWnd->ShowWindow(SW_SHOWNORMAL);
	m_pMainWnd->UpdateWindow();

	//m_pMainWnd = frame;//����ָ��Ӧ�ó���������ڵ�ָ��

	return TRUE;//���������ĳ�ʼ��
}

//��Ϣӳ��ֽ��
BEGIN_MESSAGE_MAP(MyFrame, CFrameWnd)
ON_WM_LBUTTONDOWN()//���������º�
ON_WM_CHAR()//���̰�����Ϣ�����
ON_WM_PAINT()//��ͼӳ����ں�
END_MESSAGE_MAP()

//���ڿ�ܵ�Ĭ�Ϲ��캯��
MyFrame::MyFrame()
{
	Create(NULL, TEXT("MFC WINDOW"));
}

//���������µ�ʵ��
void MyFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	//TCHAR buf[1024];
	//wsprintf(buf, TEXT("x = %d, y = %d"), point.x, point.y);
	//MessageBox(buf);

	//MFCʹ���ַ���
	CString str;
	//��ʽ���ַ���
	str.Format(TEXT(":::: x = %d, y = %d"), point.x, point.y);
	MessageBox(str);
}
//�����¼�����ʵ��
void MyFrame::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	TCHAR buf[1024];
	wsprintf(buf, TEXT("������ %c "), nChar);
	MessageBox(buf);
}
//��ͼ�¼�ʵ��
void MyFrame::OnPaint()
{
	CPaintDC dc(this);//������ǰ����
	
	//������
	dc.TextOutW(100, 100, TEXT("hello world!"));

	dc.Ellipse(10, 10, 100, 100);
}
