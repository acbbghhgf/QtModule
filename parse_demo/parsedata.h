#pragma once
#ifndef _PARSEDATA_H
#define _PARSEDATA_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "user.h"
#include "base.h"


//��ȡ��׼ģ����������
int get_model_str(std::vector<std::string>& model_strs);

//����Ŀ������ڵ�����ֵ��ֵ
float get_block_mean(cv::Mat& pic, int x, int y, int width_len, int height_len);

//ģ����ֵѵ��
int get_white_black_counter(std::vector<mdata_t>& pos, cv::Mat& pic, std::string& str);

//����ѵ�������ֵ���м���õ�������ֵ
int get_threshlod(std::vector<mdata_t>& pos);

//��ȡԭͼ��С�����ݵ�λ�á�
int get_mdata_pos(std::vector<mdata_t>& pos);

#endif // !_PARSEDATA_H

