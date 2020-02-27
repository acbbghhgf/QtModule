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

//处理容器中所有的图像还原到1：1大小
//src-输入图片容器，src_pic--输出还原图片容器
//成功返回0，失败返回-1
int RestorePic(std::vector<cv::Mat>& src, std::vector<cv::Mat>& src_pic);

//单独处理一张图片还原成1：1大小
//src_frame--输入源图片图片 dst_frame--输出处理后的图片
//成功返回0，失败返回-1
int RestorePicSingle(cv::Mat& src_frame, cv::Mat& dst_frame);

//将容器中的图片保存到本地
//FirstName--保存图片名字的开头，后跟序号, src--输入需要保存的图片容器
//成功返回0，失败返回-1
int SavePic(const char* FirstName, std::vector<cv::Mat>& src);

#endif // !_PARSEDATA_H

