#pragma once
#include <afxwin.h>//MFC��Ҫ������ͷ�ļ�

class MyApp : public CWinApp
{
public:
	//�������
	virtual BOOL InitInstance();
};

//���ڿ����
class MyFrame : public CFrameWnd
{
public:
	MyFrame();//���ڹ��캯��

	//ʹ����Ϣӳ��������
	DECLARE_MESSAGE_MAP();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);//���������µĴ���
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);//��������
	afx_msg void OnPaint();//��ͼ����


};