#include "parsedata.h"



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
    if (src.size == 0)
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

int RestorePicSingle(cv::Mat& src_frame, cv::Mat& dst_frame)
{
    //处理还原图片
    dst_frame = src_frame.clone();
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
