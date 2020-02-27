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

//�������������е�ͼ��ԭ��1��1��С
//src-����ͼƬ������src_pic--�����ԭͼƬ����
//�ɹ�����0��ʧ�ܷ���-1
int RestorePic(std::vector<cv::Mat>& src, std::vector<cv::Mat>& src_pic);

//��������һ��ͼƬ��ԭ��1��1��С
//src_frame--����ԴͼƬͼƬ dst_frame--���������ͼƬ
//�ɹ�����0��ʧ�ܷ���-1
int RestorePicSingle(cv::Mat& src_frame, cv::Mat& dst_frame);

//�������е�ͼƬ���浽����
//FirstName--����ͼƬ���ֵĿ�ͷ��������, src--������Ҫ�����ͼƬ����
//�ɹ�����0��ʧ�ܷ���-1
int SavePic(const char* FirstName, std::vector<cv::Mat>& src);

#endif // !_PARSEDATA_H

