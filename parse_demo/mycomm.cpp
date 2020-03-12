#include "mycomm.h"


int comm_test()
{
    HANDLE hCom;
    hCom = CreateFile(_T("COM1"),//COM2��
        GENERIC_READ | GENERIC_WRITE,//�������д
        0,//��ռ��ʽ
        NULL,
        OPEN_EXISTING,//�򿪶����Ǵ���
        0,//ͬ����ʽ
        NULL);
    if (hCom == (HANDLE)-1)
    {
        printf("��COMʧ��!\n");
        return FALSE;
    }
    else
    {
        printf("COM�򿪳ɹ���\n");
    }
    if (!SetupComm(hCom, 1024, 1024))//���뻺����������������Ĵ�С����1024
    {
        printf("error id = %d\n", GetLastError());
    }

    COMMTIMEOUTS TimeOuts;//�趨����ʱ    
    TimeOuts.ReadIntervalTimeout = MAXWORD;//�Ѽ����ʱ����Ϊ����ܳ�ʱ����Ϊ0������readfile�������ز���ɲ�����
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//��ʱ��ϵ��
    TimeOuts.ReadTotalTimeoutConstant = 0;//��ʱ�䳣��
    TimeOuts.WriteTotalTimeoutMultiplier = 50;//�趨д��ʱ,�ܳ�ʱ=ʱ��ϵ��*Ҫ���/д���ַ��� + ʱ�䳣��
    TimeOuts.WriteTotalTimeoutConstant = 2000;//����д��ʱ
    SetCommTimeouts(hCom, &TimeOuts);//���ó�ʱ

    DCB dcb1;
    //��ȡ���пڵ����á�
    GetCommState(hCom, &dcb1);
    dcb1.BaudRate = 115200;//������Ϊ9600
    dcb1.ByteSize = 8;//ÿ���ֽ���8λ
    dcb1.Parity = NOPARITY;//����żУ��λ
    dcb1.StopBits = TWOSTOPBITS;//����ֹͣλ
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    //���ô��пڵ�����
    SetCommState(hCom, &dcb1);

    DWORD wCount = 256;//��ȡ���ֽ���
    DWORD wCount1;
    char mbuf[] = "hello world!\n";

    PurgeComm(hCom, PURGE_TXCLEAR | PURGE_RXCLEAR);//��ջ�����
    while (1)
    {
        int i = 0;
        FILE* fp1;
        unsigned char str[256];
        //str-�������ݻ�����,wCount-��ȡ�ֽڸ�����wCount1-ʵ�ʶ�ȡ���ֽ�����ָ��
        //������
#if 0
        if (!ReadFile(hCom, str, wCount, &wCount1, NULL))
        {
            printf("������ʧ��!");
            return FALSE;
        }

        //���汾���ļ��С�
        //fp1 = fopen("���ڷ��͵���.txt", "a+");
        //if (wCount1 > 0)
        //{
        //    printf("wCount1:%d\n", wCount1);
        //}
        printf("�����ڳɹ�!��ȡ����Ϊ:\n");
        for (i = 0; i < wCount1; i++)
        {
            printf("%02X ", str[i]);
            //fprintf(fp1, "%02X ", str[i]);
        }
        printf("\n");
#endif
        if (!WriteFile(hCom, mbuf, strlen(mbuf), &wCount1, NULL))
        {
            printf("write comm fail!\n");
        }
        else
        {
            printf("send hello world comm success\n");
        }
        //fclose(fp1);
    }

    CloseHandle(hCom);

    std::cout << "Hello World!\n";

    return 0;
}

//��ʼ�������豸��Ϊ������ö�ȡ���߷��������ṩ�ӿ�
MyComm::MyComm(const wchar_t* FileName)
{
    if (comm_init(FileName) != 0)
    {
        is_opened = false;
    }
    else
    {
        is_opened = true;
    }
}

//�ڲ���ʼ���������򿨴����豸����ʼ��
//�ɹ�����0��ʧ�ܷ���-1
int MyComm::comm_init(const wchar_t* FileName)
{
    mCom = CreateFile(_T("COM9"),//COM2��
        GENERIC_READ | GENERIC_WRITE,//�������д
        0,//��ռ��ʽ
        NULL,
        OPEN_EXISTING,//�򿪶����Ǵ���
        0,//ͬ����ʽ
        NULL);
    //mCom = CreateFile(FileName,//COM2��
    //    GENERIC_READ | GENERIC_WRITE,//�������д
    //    0,//��ռ��ʽ
    //    NULL,
    //    OPEN_EXISTING,//�򿪶����Ǵ���
    //    0,//ͬ����ʽ
    //    NULL);
    if (mCom == (HANDLE)-1)
    {
        printf("��COMʧ��!\n");
        return -1;
    }
    else
    {
        printf("COM�򿪳ɹ���\n");
    }
    if (!SetupComm(mCom, 0, 0))//���뻺����������������Ĵ�С����1024
    {
        printf("error id = %d\n", GetLastError());
        return -1;
    }

    COMMTIMEOUTS TimeOuts;//�趨����ʱ    
    TimeOuts.ReadIntervalTimeout = MAXWORD;//�Ѽ����ʱ����Ϊ����ܳ�ʱ����Ϊ0������readfile�������ز���ɲ�����
    TimeOuts.ReadTotalTimeoutMultiplier = 0;//��ʱ��ϵ��
    TimeOuts.ReadTotalTimeoutConstant = 0;//��ʱ�䳣��
    TimeOuts.WriteTotalTimeoutMultiplier = 50;//�趨д��ʱ,�ܳ�ʱ=ʱ��ϵ��*Ҫ���/д���ַ��� + ʱ�䳣��
    TimeOuts.WriteTotalTimeoutConstant = 2000;//����д��ʱ
    SetCommTimeouts(mCom, &TimeOuts);//���ó�ʱ

    DCB dcb1;
    //��ȡ���пڵ����á�
    GetCommState(mCom, &dcb1);
    dcb1.BaudRate = 9600;//������Ϊ9600
    dcb1.ByteSize = 8;//ÿ���ֽ���8λ
    dcb1.Parity = NOPARITY;//����żУ��λ
    dcb1.StopBits = TWOSTOPBITS;//����ֹͣλ
    dcb1.fParity = FALSE;
    dcb1.fNull = FALSE;
    //���ô��пڵ�����
    SetCommState(mCom, &dcb1);

    return 0;
}

//���ʹ������ݣ��ɹ����ط������ݵĳ��ȣ�ʧ�ܷ���-1
int MyComm::SendData(const char* Buf, int DataLen)
{
    DWORD wCount1;
    if (!is_opened)
    {
        printf("%s:%d : comm open fail\n", __func__, __LINE__);
        return -1;
    }
    if (!WriteFile(mCom, Buf, DataLen, &wCount1, NULL))
    {
        printf("%s:%d : comm send data fail\n", __func__, __LINE__);
        return -1;
    }

    printf("%s:%d : send data success, data len : %d\n", __func__, __LINE__, wCount1);
    return wCount1;
}

//��ȡ�����豸���ݡ�
//��out��Buf--��ȡ�洢������ָ�룬��in��DataLen--��ȡ����
//�ɹ����ض�ȡʵ�ʳ��ȣ�ʧ�ܷ���-1
int MyComm::ReadData(char* Buf, int DataLen)
{
    DWORD wCount = 256;//��ȡ���ֽ���
    DWORD InfactCount = 0;
    DWORD wCount1;
    if (!is_opened)
    {
        printf("%s:%d : comm open fail\n", __func__, __LINE__);
        return -1;
    }
    if (DataLen > wCount)
    {
        while (DataLen > wCount)
        {
            
            if (!ReadFile(mCom, Buf, wCount, &wCount1, NULL))
            {
                printf("%s:%d : comm read data fail\n", __func__, __LINE__);
                if (InfactCount == 0)
                {
                    printf("%s:%d : comm read data fail\n", __func__, __LINE__);
                    return -1;
                }
                else
                {
                    printf("%s:%d : Infact send len : %d, need send len : %d\n", __func__, __LINE__, InfactCount, DataLen);
                    break;
                }
            }
            DataLen -= wCount;
            Buf += wCount1;
            InfactCount += wCount1;
        }
        if (DataLen > 0)
        {
            if (!ReadFile(mCom, Buf, DataLen, &wCount1, NULL))
            {
                printf("%s:%d : comm read data fail\n", __func__, __LINE__);
            }
            else
            {
                InfactCount += wCount1;
            }
        }
    }
    else
    {
        if (!ReadFile(mCom, Buf, DataLen, &wCount1, NULL))
        {
            printf("%s:%d : comm read data fail\n", __func__, __LINE__);
            return -1;
        }
        printf("%s:%d : rend data success, data len : %d\n", __func__, __LINE__, wCount1);
        InfactCount = wCount1;
    }
    return InfactCount;
}


int mSendToRecv(MyComm &mcom)
{
    char BCA[] = "BCA";
    char bca[] = "bca";

    //1.1�����ź�
    //����BCDA
    if (mcom.SendData(BCA, strlen(BCA)) == -1)
    {
        return -1;
    }
    //sleep
    Sleep(500);
    //����bcda
    if (mcom.SendData(bca, strlen(bca)) == -1)
    {
        return -1;
    }

    return 0;
}
