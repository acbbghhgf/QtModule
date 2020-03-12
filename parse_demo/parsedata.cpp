#include "parsedata.h"

#define SHOW_PIC    0



unsigned char getXsChar(int a, int b, int c)
{
    unsigned char ch = 0;
    if (a > 15)
    {
        ch = c * 16 + c;
    }
    else
    {
        c = (a + b) % 16;
        ch = c * 16 + c;
    }
    return ch;
}


static void get_position(mdata_t& m, int start_x, int start_y, int current_row, int current_col, int draw_width, int draw_height, \
    int four_row_num, int four_col_num)
{
    int x1, x2, y1, y2;
    int four_block_with, four_block_height;
    four_block_with = draw_width / four_row_num;
    four_block_height = draw_height / four_col_num;

    x1 = start_x + current_row * four_block_with;
    y1 = start_y + current_col * four_block_height;
    x2 = start_x + (current_col + 1) * four_block_with;
    y2 = start_y + (current_col + 1) * four_block_height;

    m.id = current_col * four_row_num + current_row;
    m.x1 = x1;
    m.y1 = y1;
    m.x2 = x2;
    m.y2 = y2;
    m.black_counter = 0.0;
    m.white_counter = 255;
    m.threshold = 0.0;
}

int get_mdata_pos(std::vector<mdata_t>& pos)
{
    pos.clear();
    mdata_t tmp_m;
    for (int cur_y = 0; cur_y < FOUR_BLOCK_ROW_NUM; ++cur_y)
    {
        for (int cur_x = 0; cur_x < FOUR_BLOCK_COL_NUM; cur_x++)
        {
            get_position(tmp_m, START_X, START_Y, cur_x, cur_y, DRAW_WIDTH, DRAW_HEIGHT, FOUR_BLOCK_COL_NUM, FOUR_BLOCK_ROW_NUM);
            pos.push_back(tmp_m);
        }
    }

    for (auto it = pos.begin(); it != pos.end(); ++it)
    {
        std::cout << "pos id = " << it->id << std::endl;
    }

    return 0;
}


int get_model_str(std::vector<std::string>& model_strs)
{
    model_strs.clear();
    for (int i = 0; i < 20; ++i)
    {
        std::string model_str_one;
        if (i > 15)
        {
            for (int j = 0; j < FOUR_BLOCK_ROW_NUM * FOUR_BLOCK_COL_NUM / 2; ++j)
            {
                int temp = 0;
                switch (i)
                {
                case 16:
                    temp = 0;
                    break;
                case 17:
                    temp = 6;
                    break;
                case 18:
                    temp = 9;
                    break;
                default:
                    break;
                }
                unsigned char ch;
                ch = getXsChar(i, 0, temp);
                model_str_one.push_back(ch);
            }
        }
        else
        {
            for (int j = 0; j < FOUR_BLOCK_ROW_NUM; j++)
            {
                unsigned char ch = getXsChar(i, j, 0);
                for (int k = 0; k < FOUR_BLOCK_COL_NUM / 2; k++)
                {
                    model_str_one.push_back(ch);
                }
            }
        }
        model_strs.push_back(model_str_one);
    }
    return 0;
}

float get_block_mean(cv::Mat &pic, int x, int y, int width_len, int height_len)
{
    //std::cout << "pic.channls = " << pic.channels() << std::endl;
    cv::Vec3b m;
    float a = 0.0;
    int counter = 0;
    for (int i = x; i < x + width_len; i++)
    {
        for (int j = y; j < y + height_len; j++)
        {
            a += pic.at<uchar>(cv::Point(i, j));
            counter++;
        }
    }
    if (!counter)
    {
        return 0.0;
    }
    return a / counter;
}

//输入低4位字节数据及对应的坐标从图片中获取目标区域的像素均值进行处理
//黑色为1 白色为0
// 1 2
// 4 8
void white_black_process(mdata_t& m, char low_four, cv::Mat& pic)
{
    int four_block_x1 = m.x1;
    int four_block_y1 = m.y1;
    int four_block_x2 = m.x2;
    int four_block_y2 = m.y2;
    int mid_x, mid_y;
    mid_x = (four_block_x2 + four_block_x1) / 2;
    mid_y = (four_block_y1 + four_block_y2) / 2;
    
    float black_threshold = 0.0;
    float white_threshold = 255;

    uchar byte = low_four & 0x0f;

    if (byte & 0x01)
    {
        //1位为1
        black_threshold = get_block_mean(pic, four_block_x1, four_block_y1, mid_x - four_block_x1, mid_y - four_block_y1);
        if (black_threshold > m.black_counter)
        {
            m.black_counter = black_threshold;
        }
    }
    else {
        white_threshold = get_block_mean(pic, four_block_x1, four_block_y1, mid_x - four_block_x1, mid_y - four_block_y1);
        if (white_threshold < m.white_counter)
        {
            m.white_counter = white_threshold;
        }
    }
    if (byte & 0x02)
    {
        //2位为1
        black_threshold = get_block_mean(pic, mid_x, four_block_y1, four_block_x2 - mid_x, mid_y - four_block_y1);
        if (black_threshold > m.black_counter)
        {
            m.black_counter = black_threshold;
        }
    }
    else {
        white_threshold = get_block_mean(pic, mid_x, four_block_y1, four_block_x2 - mid_x, mid_y - four_block_y1);
        if (white_threshold < m.white_counter)
        {
            m.white_counter = white_threshold;
        }
    }
    if (byte & 0x04)
    {
        //4位为1
        black_threshold = get_block_mean(pic, four_block_x1, mid_y, mid_x - four_block_x1, four_block_y2 - mid_y);
        if (black_threshold > m.black_counter)
        {
            m.black_counter = black_threshold;
        }
    }
    else {
        white_threshold = get_block_mean(pic, four_block_x1, mid_y, mid_x - four_block_x1, four_block_y2 - mid_y);
        if (white_threshold < m.white_counter)
        {
            m.white_counter = white_threshold;
        }
    }
    if (byte & 0x08)
    {
        //8位为1
        black_threshold = get_block_mean(pic, mid_x, mid_y, four_block_x2 - mid_x, four_block_y2 - mid_y);
        if (black_threshold > m.black_counter)
        {
            m.black_counter = black_threshold;
        }
    }
    else {
        white_threshold = get_block_mean(pic, mid_x, mid_y, four_block_x2 - mid_x, four_block_y2 - mid_y);
        if (white_threshold < m.white_counter)
        {
            m.white_counter = white_threshold;
        }

    }

}

//m内存放有每一个田字格的坐标，而str存放了图片数据，pic是这张1:1的源图像。
//根据数据得到每一个田字格中的黑白情况，将黑白阈值赋值给m结构体内。
int get_white_black_counter(std::vector<mdata_t> &pos, cv::Mat& pic, std::string& str)
{   
    char tmpstr;
    for (auto it = pos.begin(); it != pos.end(); ++it)
    {
        if ((it - pos.begin()) % 2 == 0)
        {
            tmpstr = (uchar)str[(it - pos.begin()) / 2];
            //高4位
            white_black_process(*it, tmpstr >> 4, pic);
        }
        else
        {
            //低4位
            white_black_process(*it, tmpstr & 0x0f, pic);
        }
    }
    return 0;
}


int get_threshlod(std::vector<mdata_t>& pos)
{
    for (auto it = pos.begin(); it != pos.end(); ++it)
    {
        it->threshold = (it->black_counter + it->white_counter) / 2;
    }
    return 0;
}


int RestorePic(std::vector<cv::Mat>& src, std::vector<cv::Mat>& src_pic)
{
    if (src.size() == 0)
    {
        printf("%s : %d : src vector is empty!\n", __func__, __LINE__);
        return -1;
    }

    src_pic.clear();
    cv::Mat src_frame;
    cv::Mat dst_frame;
    for (auto it = src.begin(); it != src.end(); ++it)
    {
        src_frame = it->clone();
        //处理每一张图片
        if (RestorePicSingle(src_frame, dst_frame) == -1)
        {
            printf("%s : %d : src frame restore error.\n", __func__, __LINE__);
            return -1;
        }
        src_pic.push_back(dst_frame);
    }
    assert(src_pic.size() == 20);
    return 0;
}
//
//
//static int get_restore_pic(cv::Mat& src_frame, cv::Mat& dst_frame)
//{
//    if (src_frame.empty())
//    {
//        std::cerr << "read pic failed !!!!!" << std::endl;
//        return -1;
//    }
//    else
//    {
//        auto start_time = std::chrono::system_clock::now();//计时start---------------
//
//        std::string win_name1("src image");
//
//        cv::Mat src_gray;
//        //转灰度图
//        cv::cvtColor(src_frame, src_gray, cv::COLOR_BGR2GRAY);
//        //平滑处理
//        cv::blur(src_gray, src_gray, cv::Size(3, 3));
//        //直方图均衡化
//        cv::equalizeHist(src_gray, src_gray);
//        
//        //指定112阈值进行二值化
//#if SHOW_PIC
//        my_show_pic("equalize", src_gray);
//#endif
//        cv::Mat src_threshold;
//        cv::threshold(src_gray, src_threshold, 100, 255, cv::THRESH_BINARY);
//        
//#if SHOW_PIC
//        my_show_pic("threshold", src_threshold);
//#endif
//        cv::Scalar color(1, 1, 255);
//        std::vector<std::vector<cv::Point>> contours;
//        std::vector<cv::Vec4i> hierarchy;
//        cv::Mat draw1 = cv::Mat::zeros(src_frame.size(), CV_8UC3);
//        cv::Mat draw2 = cv::Mat::zeros(src_frame.size(), CV_8UC3);
//
//        findContours(src_threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));
//
//        struct index
//        {
//            int a1;
//            int a2;
//            int a3;
//            int a4;
//        };
//        int temp_index1 = 0;
//        int temp_index2 = 0;
//        int temp_index3 = 0;
//        std::vector<index>vin;
//
//#if 0
//
//        for (int i = 0; i < contours.size(); ++i)
//        {
//            //std::cout << "hierarchy the [" << i << "] is " << (hierarchy)[i] << std::endl;
//            if ((hierarchy)[i][3] == -1)
//            {
//                continue;
//            }
//            else
//            {
//                temp_index1 = (hierarchy)[i][3];
//
//            }
//            if ((hierarchy)[temp_index1][3] == -1)
//            {
//                continue;
//            }
//            else
//            {
//                temp_index2 = (hierarchy)[temp_index1][3];
//            }
//            if ((hierarchy)[temp_index2][3] == -1)
//            {
//                continue;
//            }
//            else
//            {
//                temp_index3 = (hierarchy)[temp_index2][3];
//                index in;
//                in.a1 = i;
//                in.a2 = temp_index1;
//                in.a3 = temp_index2;
//                in.a4 = temp_index3;
//                vin.push_back(in);
//            }
//        }
//
//
//        //std::cout << "construct vin over: " << vin.size() << std::endl;
//        int count = 0;
//        for (auto it = vin.begin(); it != vin.end();)
//        {
//            cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 0, 0), FILLED, 8);
//            it++;
//        }
//        //std::cout << "total count is " << count << std::endl;
//        std::string win_name4("search_contours");
//        //cv::namedWindow(win_name4);
//        //cv::imshow(win_name4, draw1);
//        //cv::waitKey(0);
//#else
//
//        for (int i = 0; i < contours.size(); ++i)
//        {
//            //std::cout << "hierarchy the [" << i << "] is " << (hierarchy)[i] << std::endl;
//            if ((hierarchy)[i][2] == -1)
//            {
//                continue;
//            }
//            else
//            {
//                temp_index1 = (hierarchy)[i][2];
//
//            }
//            if ((hierarchy)[temp_index1][2] == -1)
//            {
//                continue;
//            }
//            else
//            {
//                temp_index2 = (hierarchy)[temp_index1][2];
//                index in;
//                in.a1 = i;
//                in.a2 = temp_index1;
//                in.a3 = temp_index2;
//                vin.push_back(in);
//            }
//        }
//
//        int count = 0;
//        for (auto it = vin.begin(); it != vin.end();)
//        {
//            count += 1;
//            std::vector<cv::Point> contours_out1 = (contours)[it->a1];
//            std::vector<cv::Point> contours_out2 = (contours)[it->a2];
//            double len1 = cv::arcLength(contours_out1, 1);
//            //std::cout << "len1 : " << len1 << std::endl;
//            double len2 = cv::arcLength(contours_out2, 1);
//            //std::cout << "len2 : " << len2 << std::endl;
//
//            if (abs(len1 / len2 - 2) > 1)
//            {
//                it = vin.erase(it);
//            }
//            else
//            {
//                cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), cv::FILLED, 8);
//                it++;
//            }
//
//        }
//#endif
//
//        int i = 0;
//        std::vector<std::vector<cv::Point>> target_contours;
//        for (auto it = vin.begin(); it != vin.end(); ++it)
//        {
//            target_contours.push_back((contours)[it->a1]);
//        }
//
//
//        std::vector<cv::Moments> mu(target_contours.size());
//        for (int i = 0; i < target_contours.size(); i++)
//        {
//            mu[i] = cv::moments(target_contours[i], false);
//        }
//        std::vector<cv::Point2i> mc(target_contours.size());
//        for (int i = 0; i < target_contours.size(); ++i)
//        {
//            mc[i] = cv::Point2i(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
//            //std::cout << "mc " << i << " is " << mc[i] << std::endl;
//        }
//
//        //auto end_time = std::chrono::system_clock::now();//-计时end----------------------
//        //std::cout << "time duration is " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;
//
//        std::cout << "mc size is : " << mc.size() << std::endl;
//        if (mc.size() != 4)
//        {
//            std::cout << __func__ << ":" << __LINE__ << ": " << "mc size is no 4--error" << std::endl;
//            return -1;
//        }
//        cv::Mat drawing = cv::Mat::zeros(src_frame.size(), CV_8UC3);
//        for (int i = 0; i < target_contours.size(); i++)
//        {
//            cv::drawContours(drawing, target_contours, i, CV_RGB(255, 255, 255), -1, 8);
//            cv::circle(drawing, mc[i], 4, color, -1, 8, 0);
//            cv::line(drawing, mc[i % mc.size()], mc[(i + 1) % mc.size()], color);
//        }
//#if SHOW_PIC
//        my_show_pic("drawing", drawing);
//#endif
//        auto cmp = [](cv::Point2i& a, cv::Point2i& b) {return a.x < b.x; };
//        auto cmp2 = [](cv::Point2i& a, cv::Point2i& b) {return a.y < b.y; };
//        auto cmp3 = [](cv::Point2i& a, cv::Point2i& b) {return a.y > b.y; };
//
//        std::sort(mc.begin(), mc.end(), cmp);
//        std::sort(mc.begin(), mc.begin() + 2, cmp2);
//        std::sort(mc.begin() + 2, mc.end(), cmp3);
//        for (auto it = mc.begin(); it != mc.end(); it++)
//        {
//            std::cout << *it << std::endl;
//        }
//        cv::Point2f src_points[] = { mc[0],mc[1],mc[2] ,mc[3] };
//
//
//        cv::Point2f dst_points[] = { cv::Point2f(CONTOURS_X, CONTOURS_Y), cv::Point2f(CONTOURS_X, CONTOURS_Y + CONTOURS_HEIGHT), cv::Point2f(CONTOURS_X + CONTOURS_WIDTH, CONTOURS_Y + CONTOURS_HEIGHT), cv::Point2f(CONTOURS_X + CONTOURS_WIDTH, CONTOURS_Y) };
//
//        cv::Mat trans_matrix = cv::getPerspectiveTransform(src_points, dst_points);
//        cv::Mat trans_pic = cv::Mat::zeros(cv::Size(1920, 1200), CV_8UC3);
//
//        cv::warpPerspective(src_frame, trans_pic, trans_matrix, cv::Size(1920, 1200), cv::INTER_LINEAR);
//
//        getRectSubPix(trans_pic, cv::Size(SOURCE_SIZE_WIDTH, SOURCE_SIZE_HEIGHT), cv::Point2f(512, 300), dst_frame);
//#if SHOW_PIC
//        my_show_pic("dst", dst_frame);
//#endif
//    }
//    return 0;
//}

static int findtarget_contours(std::vector<cv::Vec4i>& hierarchy, std::vector<std::vector<cv::Point>> &contours,std::vector<std::vector<cv::Point>>& target_contours)
{
    struct index
    {
        int a1;
        int a2;
        int a3;
        int a4;
    };
    int temp_index1 = 0;
    int temp_index2 = 0;
    int temp_index3 = 0;
    std::vector<index>vin;


    for (int i = 0; i < contours.size(); ++i)
    {
        //std::cout << "hierarchy the [" << i << "] is " << (hierarchy)[i] << std::endl;
        if ((hierarchy)[i][2] == -1)
        {
            continue;
        }
        else
        {
            temp_index1 = (hierarchy)[i][2];

        }
        if ((hierarchy)[temp_index1][2] == -1)
        {
            continue;
        }
        else
        {
            temp_index2 = (hierarchy)[temp_index1][2];
            index in;
            in.a1 = i;
            in.a2 = temp_index1;
            in.a3 = temp_index2;
            vin.push_back(in);
        }
    }

    int count = 0;
    for (auto it = vin.begin(); it != vin.end();)
    {
        count += 1;
        std::vector<cv::Point> contours_out1 = (contours)[it->a1];
        std::vector<cv::Point> contours_out2 = (contours)[it->a2];
        double len1 = cv::arcLength(contours_out1, 1);
        //std::cout << "len1 : " << len1 << std::endl;
        double len2 = cv::arcLength(contours_out2, 1);
        //std::cout << "len2 : " << len2 << std::endl;

        if (abs(len1 / len2 - 2) > 1)
        {
            it = vin.erase(it);
        }
        else
        {
            //cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), cv::FILLED, 8);
            it++;
        }

    }

    int i = 0;
    for (auto it = vin.begin(); it != vin.end(); ++it)
    {
        target_contours.push_back((contours)[it->a1]);
    }

    return target_contours.size();

}

static int get_threshold_value(cv::Mat &src)
{
    int dstThresholdValue = 0;
    int targetNum = 0;

    if (src.empty())
    {
        std::cerr << "get_threshold_value pic failed !!!!!" << std::endl;
        return -1;
    }
   
        cv::Mat src_gray;
        //转灰度图
        cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
        //平滑处理
        cv::blur(src_gray, src_gray, cv::Size(3, 3));
        //直方图均衡化
        cv::equalizeHist(src_gray, src_gray);

        while (dstThresholdValue < 255)
        {
            //指定112阈值进行二值化
            cv::Mat src_threshold;
            cv::threshold(src_gray, src_threshold, dstThresholdValue, 255, cv::THRESH_BINARY);


            std::vector<std::vector<cv::Point>> contours;
            std::vector<cv::Vec4i> hierarchy;

            findContours(src_threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));

            std::vector<std::vector<cv::Point>> target_contours;
            targetNum = findtarget_contours(hierarchy, contours, target_contours);
            if (targetNum == 4)
            {
                std::cout << __func__ << " : " << __LINE__ << ": findtargetNum = 4 success " << std::endl;
                return dstThresholdValue;
            }
            dstThresholdValue += 10;

        }

    return -1;
}

static bool findThreshold = false;
static int threshold = 0;

static int get_restore_pic(cv::Mat& src_frame, cv::Mat& dst_frame)
{
    if (src_frame.empty())
    {
        std::cerr << "read pic failed !!!!!" << std::endl;
        return -1;
    }
    else
    {
        if (!findThreshold)
        {
            threshold = get_threshold_value(src_frame);
            if (threshold == -1)
            {

                std::cerr << __func__  << " : " << __LINE__ <<  " : find threshold error !!!!!" << std::endl;
                return -1;
            }
            findThreshold = true;
        }
        auto start_time = std::chrono::system_clock::now();//计时start---------------

        std::string win_name1("src image");

        cv::Mat src_gray;
        //转灰度图
        cv::cvtColor(src_frame, src_gray, cv::COLOR_BGR2GRAY);
        //平滑处理
        cv::blur(src_gray, src_gray, cv::Size(3, 3));
        //直方图均衡化
        cv::equalizeHist(src_gray, src_gray);

        //指定112阈值进行二值化
#if SHOW_PIC
        my_show_pic("equalize", src_gray);
#endif
        cv::Mat src_threshold;
        cv::threshold(src_gray, src_threshold, threshold, 255, cv::THRESH_BINARY);

#if SHOW_PIC
        my_show_pic("threshold", src_threshold);
#endif
        cv::Scalar color(1, 1, 255);
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::Mat draw1 = cv::Mat::zeros(src_frame.size(), CV_8UC3);
        cv::Mat draw2 = cv::Mat::zeros(src_frame.size(), CV_8UC3);

        findContours(src_threshold, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));

        struct index
        {
            int a1;
            int a2;
            int a3;
            int a4;
        };
        int temp_index1 = 0;
        int temp_index2 = 0;
        int temp_index3 = 0;
        std::vector<index>vin;


        for (int i = 0; i < contours.size(); ++i)
        {
            //std::cout << "hierarchy the [" << i << "] is " << (hierarchy)[i] << std::endl;
            if ((hierarchy)[i][2] == -1)
            {
                continue;
            }
            else
            {
                temp_index1 = (hierarchy)[i][2];

            }
            if ((hierarchy)[temp_index1][2] == -1)
            {
                continue;
            }
            else
            {
                temp_index2 = (hierarchy)[temp_index1][2];
                index in;
                in.a1 = i;
                in.a2 = temp_index1;
                in.a3 = temp_index2;
                vin.push_back(in);
            }
        }

        int count = 0;
        for (auto it = vin.begin(); it != vin.end();)
        {
            count += 1;
            std::vector<cv::Point> contours_out1 = (contours)[it->a1];
            std::vector<cv::Point> contours_out2 = (contours)[it->a2];
            double len1 = cv::arcLength(contours_out1, 1);
            //std::cout << "len1 : " << len1 << std::endl;
            double len2 = cv::arcLength(contours_out2, 1);
            //std::cout << "len2 : " << len2 << std::endl;

            if (abs(len1 / len2 - 2) > 1)
            {
                it = vin.erase(it);
            }
            else
            {
                cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), cv::FILLED, 8);
                it++;
            }

        }

        int i = 0;
        std::vector<std::vector<cv::Point>> target_contours;
        for (auto it = vin.begin(); it != vin.end(); ++it)
        {
            target_contours.push_back((contours)[it->a1]);
        }


        std::vector<cv::Moments> mu(target_contours.size());
        for (int i = 0; i < target_contours.size(); i++)
        {
            mu[i] = cv::moments(target_contours[i], false);
        }
        std::vector<cv::Point2i> mc(target_contours.size());
        for (int i = 0; i < target_contours.size(); ++i)
        {
            mc[i] = cv::Point2i(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);
            //std::cout << "mc " << i << " is " << mc[i] << std::endl;
        }

        //auto end_time = std::chrono::system_clock::now();//-计时end----------------------
        //std::cout << "time duration is " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;

        std::cout << "mc size is : " << mc.size() << std::endl;
        if (mc.size() != 4)
        {
            std::cout << __func__ << ":" << __LINE__ << ": " << "mc size is no 4--error" << std::endl;
            return -1;
        }
        cv::Mat drawing = cv::Mat::zeros(src_frame.size(), CV_8UC3);
        for (int i = 0; i < target_contours.size(); i++)
        {
            cv::drawContours(drawing, target_contours, i, CV_RGB(255, 255, 255), -1, 8);
            cv::circle(drawing, mc[i], 4, color, -1, 8, 0);
            cv::line(drawing, mc[i % mc.size()], mc[(i + 1) % mc.size()], color);
        }
#if SHOW_PIC
        my_show_pic("drawing", drawing);
#endif
        auto cmp = [](cv::Point2i& a, cv::Point2i& b) {return a.x < b.x; };
        auto cmp2 = [](cv::Point2i& a, cv::Point2i& b) {return a.y < b.y; };
        auto cmp3 = [](cv::Point2i& a, cv::Point2i& b) {return a.y > b.y; };

        std::sort(mc.begin(), mc.end(), cmp);
        std::sort(mc.begin(), mc.begin() + 2, cmp2);
        std::sort(mc.begin() + 2, mc.end(), cmp3);
        for (auto it = mc.begin(); it != mc.end(); it++)
        {
            std::cout << *it << std::endl;
        }
        cv::Point2f src_points[] = { mc[0],mc[1],mc[2] ,mc[3] };


        cv::Point2f dst_points[] = { cv::Point2f(CONTOURS_X, CONTOURS_Y), cv::Point2f(CONTOURS_X, CONTOURS_Y + CONTOURS_HEIGHT), cv::Point2f(CONTOURS_X + CONTOURS_WIDTH, CONTOURS_Y + CONTOURS_HEIGHT), cv::Point2f(CONTOURS_X + CONTOURS_WIDTH, CONTOURS_Y) };

        cv::Mat trans_matrix = cv::getPerspectiveTransform(src_points, dst_points);
        cv::Mat trans_pic = cv::Mat::zeros(cv::Size(1920, 1200), CV_8UC3);

        cv::warpPerspective(src_frame, trans_pic, trans_matrix, cv::Size(1920, 1200), cv::INTER_LINEAR);

        getRectSubPix(trans_pic, cv::Size(SOURCE_SIZE_WIDTH, SOURCE_SIZE_HEIGHT), cv::Point2f(512, 300), dst_frame);
#if SHOW_PIC
        my_show_pic("dst", dst_frame);
#endif
    }
    return 0;
}

int RestorePicSingle(cv::Mat& src_frame, cv::Mat& dst_frame)
{
    //处理还原图片
    if (get_restore_pic(src_frame, dst_frame) == -1)
    {
        printf("%s : %d : get restore pic error!\n", __func__, __LINE__);
        return -1;
    }
    return 0;
}

int SavePic(const char* FirstName, std::vector<cv::Mat>& src)
{
    if (src.size() == 0)
    {
        printf("%s : %d : input src vector is empty!\n", __func__, __LINE__);
        return -1;
    }
    std::string FirstNameStr = FirstName;
    std::string IntactName;
    std::string Suffix = ".bmp";
    for (auto it = src.begin(); it != src.end(); ++it)
    {
        IntactName = FirstNameStr + std::to_string(it - src.begin()) + Suffix;
        cv::imwrite(IntactName, *it);
    }
    return 0;
}