#pragma once

#ifndef  IMAGE_PROCESS_H
#define IMAGE_PROCESS_H

#include <opencv2/opencv.hpp>

#include <chrono>
#include <bitset>

int process_demo_1();

void my_show_pic(std::string win_name, cv::Mat& pic);

void image_read_data_demo();

#if 0
//int capture_param_test_read_data(std::vector<my_mat_t>& test_capture, my_mat_t& dst_param);
//
//int capture_param_test_process(std::vector<my_mat_t>& test_capture);
//
//
//int capture_param_test_process_sigle(my_mat_t& test_capture_sigle);
//
//double capture_param_test_read_data_sigle(my_mat_t& test_capture_sigle);
#endif

#endif // ! IMAGE_PROCESS_H

