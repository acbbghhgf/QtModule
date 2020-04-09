#include <Windows.h>

//������Ϣ
LRESULT CALLBACK Windowproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN://�������
    {
        int xPos, yPos;
        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);

        //��ӡ����
        TCHAR buf[1024];
        wsprintf(buf, TEXT("x = %d, y = %d "), xPos, yPos);
        MessageBox(hwnd, buf, TEXT("��갴��"), MB_OK);
    }
    break;
    case WM_KEYDOWN://���¼���
        MessageBox(hwnd, TEXT("���̰���"), TEXT("������Ϣ"), MB_OK);
        break;
    case WM_PAINT://��ͼ��Ϣ
    {
        PAINTSTRUCT ps;//��ͼ�ṹ��
        HDC hdc = BeginPaint(hwnd, &ps);
        //��������
        TextOut(hdc, 100, 100, TEXT("hello world"), strlen("hello world"));
        EndPaint(hwnd, &ps);
    }
        break;
    default:
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    //ʵ�ֵײ㴰�ڲ���
    //1����ƴ�����
    //2��ע�ᴰ����
    //3������������
    //4��ͨ��ѭ����ȡ��Ϣ
    //5��������Ϣ�����ڹ��̣�

    //��ƴ���
    WNDCLASS wc;
    wc.cbClsExtra = 0;//�����ڴ�Ϊ0
    wc.cbWndExtra = 0;//���ڶ����ڴ�
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//���ñ���
    wc.hCursor = LoadCursor(NULL, IDC_HAND);//���ù��
    wc.hIcon = LoadIcon(NULL, IDI_WARNING);//�������
    wc.hInstance = hInstance;//��ǰʵ�����.
    wc.lpfnWndProc = Windowproc;//���ڹ��̻ص�����.�Զ���
    wc.lpszClassName = TEXT("WINDOW");//ָ����������
    wc.lpszMenuName = NULL;//�˵���
    wc.style = 0;//Ĭ�Ϸ��

    //ע�ᴰ����
    RegisterClass(&wc);

    //����������
    /*
    lpClassName, ����
    lpWindowName, ������
    dwStyle, ��ʾ���
    x, y, ������ʼ����
    nWidth,���ڿ��
    nHeight,�߶�
    hWndParent,�����ڣ� NULL
    hMenu, �˵���NULL
    hInstance,ʵ�����
    lpParam����������
    */
    HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("TEXT WINDOW"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //��ʾ�͸���
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    //ͨ��ѭ��ȡ��Ϣ
    MSG msg;
    while (1)
    {
        if (GetMessage(&msg, NULL, 0, 0) == FALSE)
        {
            break;
        }

        //������Ϣ
        TranslateMessage(&msg);

        //�ַ���Ϣ
        DispatchMessage(&msg);
    }

    return 0;
}