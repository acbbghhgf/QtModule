// parse_demo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "parsedata.h"
#include <iostream>
#include <opencv2/opencv.hpp>
#include "sqlite/sqlite3.h"
#include "user.h"
#include "mycomm.h"


/*
模版训练模块
str--【in】标准模版字符数据。
src_pic--【in】还原到1：1大小的标准模版图片，与str 一一对应的。

成功返回0，失败返回-1
*/
int Template_train(std::vector<std::string>& str, std::vector<cv::Mat>& src_pic)
{
    std::vector<mdata_t> pos;
    //获取标准图片中数据区域坐标。
    get_mdata_pos(pos);
    std::cout << "get pos size = " << pos.size() << std::endl;

    my_table_create();
    //塞入数据库

    //打印数据库内容
    //my_table_query_print();

    //2.遍历图片填补white_counter 和 black_counter数据。
    //white 取最小值，black取最大值

    for (auto it = src_pic.begin(); it != src_pic.end(); ++it)
    {
        get_white_black_counter(pos, *it, str[it - src_pic.begin()]);
    }

    get_threshlod(pos);

    for (auto it = pos.begin(); it != pos.end(); ++it)
    {
        my_table_replace_withmdata(&(*it));
    }

    User* data_head = NULL;
    data_head = my_table_query();

    return 0;
}

/*
获取模版图片，此时将获取的原图保存到本地并编号，将图片四角定位还原后的图片塞入队列返回。
src--[out]获取到的模版拍照原图
src_pic--[out]将获取到的模版原图1：1还原处理后的图片。

成功返回0，失败返回-1
*/
int get_template_pic(std::vector<cv::Mat> &src, std::vector<cv::Mat> &src_pic)
{
    //1.给串口发送信号，sleep(1)后拍照保存。
    //添加串口消息操作。
    //循环操作第一步20次获取到20张标准模版图片。

    //2.将获取到的图片进行1：1还原处理并保存本地。
    //添加四角定位还原图片操作。
    return 0;
}

#if 0
//1.发送串口消息告知2号机显示模版调试标准图片，拍照获取图片存储本地及内存中。
//2.进入正常的模版训练模块。

int main()
{

//第一步：发送串口数据告知2号机显示模版标准图片，拍照获取图片保存记录。

    std::vector<std::string> str;//图片对应的数据
    //获取图片对应的数据。
    get_model_str(str);


    std::vector<cv::Mat> src_pic;//本地存储的图片
    std::vector<std::string> pic_name;//本地存储的图片名字
    


    for (int i = 0; i < 21; i++)
    {//获取存储图片的文件名
        std::string tmp = DEMO_DIR + std::to_string(i) + ".bmp";
        pic_name.push_back(tmp);
    }

    for (auto it = pic_name.begin(); it != pic_name.end(); ++it)
    {//获取图片
        cv::Mat src = cv::imread(*it);
        if (!src.empty())
        {
            cv::cvtColor(src, src, cv::COLOR_RGB2GRAY);
            //std::cout << "src.channles = " << src.channels() << std::endl;
            src_pic.push_back(src);
        }
    }
    std::cout << "src_pic size = " << src_pic.size() << " str.size = " << str.size() << std::endl;
    ////显示图片
    //for (auto it = src_pic.begin(); it != src_pic.end(); ++it)
    //{
    //    cv::imshow(std::to_string(it - src_pic.begin()), *it);
    //    cv::waitKey(1);
    //}

#if 1
    //第二步，训练模版
    //----------------------------
    //1.获取坐标值，将坐标值塞入数据库   
    Template_train(str, src_pic);

#endif

    return 0;
}

#else

//sigle process
int main()
{
    comm_test();
}

#endif