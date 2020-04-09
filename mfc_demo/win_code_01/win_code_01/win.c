#include <Windows.h>

//处理消息
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
    case WM_LBUTTONDOWN://左键按下
    {
        int xPos, yPos;
        xPos = LOWORD(lParam);
        yPos = HIWORD(lParam);

        //打印操作
        TCHAR buf[1024];
        wsprintf(buf, TEXT("x = %d, y = %d "), xPos, yPos);
        MessageBox(hwnd, buf, TEXT("鼠标按下"), MB_OK);
    }
    break;
    case WM_KEYDOWN://按下键盘
        MessageBox(hwnd, TEXT("键盘按下"), TEXT("键盘消息"), MB_OK);
        break;
    case WM_PAINT://绘图消息
    {
        PAINTSTRUCT ps;//绘图结构体
        HDC hdc = BeginPaint(hwnd, &ps);
        //绘制文字
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
    //实现底层窗口步骤
    //1、设计窗口类
    //2、注册窗口类
    //3、创建窗口类
    //4、通过循环获取消息
    //5、处理消息（窗口过程）

    //设计窗口
    WNDCLASS wc;
    wc.cbClsExtra = 0;//额外内存为0
    wc.cbWndExtra = 0;//窗口额外内存
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//设置背景
    wc.hCursor = LoadCursor(NULL, IDC_HAND);//设置光标
    wc.hIcon = LoadIcon(NULL, IDI_WARNING);//设置鼠标
    wc.hInstance = hInstance;//当前实例句柄.
    wc.lpfnWndProc = Windowproc;//窗口过程回调函数.自定义
    wc.lpszClassName = TEXT("WINDOW");//指定窗口类名
    wc.lpszMenuName = NULL;//菜单名
    wc.style = 0;//默认风格

    //注册窗口类
    RegisterClass(&wc);

    //创建窗口类
    /*
    lpClassName, 类名
    lpWindowName, 窗口名
    dwStyle, 显示风格
    x, y, 窗口起始坐标
    nWidth,窗口宽度
    nHeight,高度
    hWndParent,父窗口， NULL
    hMenu, 菜单，NULL
    hInstance,实例句柄
    lpParam，其他参数
    */
    HWND hwnd = CreateWindow(wc.lpszClassName, TEXT("TEXT WINDOW"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

    //显示和更新
    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);

    //通过循环取消息
    MSG msg;
    while (1)
    {
        if (GetMessage(&msg, NULL, 0, 0) == FALSE)
        {
            break;
        }

        //翻译消息
        TranslateMessage(&msg);

        //分发消息
        DispatchMessage(&msg);
    }

    return 0;
}