#pragma once
#ifndef _PARSEDATA_H
#define _PARSEDATA_H

#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include "user.h"
#include "base.h"


//获取标准模版数据内容
int get_model_str(std::vector<std::string>& model_strs);

//计算目标矩阵内的像素值均值
float get_block_mean(cv::Mat& pic, int x, int y, int width_len, int height_len);

//模版阈值训练
int get_white_black_counter(std::vector<mdata_t>& pos, cv::Mat& pic, std::string& str);

//经过训练后的阈值进行计算得到最终阈值
int get_threshlod(std::vector<mdata_t>& pos);

//获取原图大小的数据点位置。
int get_mdata_pos(std::vector<mdata_t>& pos);

#endif // !_PARSEDATA_H

