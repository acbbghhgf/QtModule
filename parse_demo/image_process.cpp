#include "image_process.h"

// qr_decode.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace cv;


void my_show_pic(std::string win_name, cv::Mat& pic)
{
	cv::namedWindow(win_name, WINDOW_AUTOSIZE);
	cv::imshow(win_name, pic);
	cv::waitKey(0);
}



int process_demo_1()
{
	//cv::Mat src = cv::imread("G:\\Dopamine\\qr_decode\\Release\\1.bmp");
	//cv::Mat src = cv::imread("2.png");
	//cv::Mat src = cv::imread("newframe.png");

	//cv::Mat src = cv::imread("BLACK_newframe.png");
	cv::Mat src = cv::imread("prop_7.png");
	//cv::Mat src = cv::imread("qr_code_9.png");


	if (src.empty())
	{
		//TCHAR buff[260];
		//GetModuleFileName(NULL, buff, 260);
		std::cerr << "read pic failed !!!!!" << std::endl;
	}
	else
	{
		auto start_time = std::chrono::system_clock::now();//---------------

		std::string win_name1("src image");
		//cv::namedWindow(win_name1, 1);
		//cv::imshow(win_name1, src);
		//cv::waitKey(0);
		cv::Mat src_gray;
		//转灰度图
		cv::cvtColor(src, src_gray, cv::COLOR_BGR2GRAY);
		//平滑处理
		cv::blur(src_gray, src_gray, cv::Size(3, 3));
		//直方图均衡化
		cv::equalizeHist(src_gray, src_gray);
		//std::string win_name2("gray--blur--hist");
		//cv::namedWindow(win_name2, 1);
		//cv::imshow(win_name2, src_gray);
		//cv::waitKey(0);
		//指定112阈值进行二值化
		cv::Mat src_threshold;
		cv::threshold(src_gray, src_threshold, 100, 255, cv::THRESH_BINARY);
		std::string win_name3("112--threshold");
		//cv::namedWindow(win_name3);
		//cv::imshow(win_name3, src_threshold);
		//cv::waitKey(0);

		cv::Scalar color(1, 1, 255);
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::Mat draw1 = cv::Mat::zeros(src.size(), CV_8UC3);
		cv::Mat draw2 = cv::Mat::zeros(src.size(), CV_8UC3);

		findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, cv::Point(0, 0));

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

#if 0

		for (int i = 0; i < contours.size(); ++i)
		{
			//std::cout << "hierarchy the [" << i << "] is " << (hierarchy)[i] << std::endl;
			if ((hierarchy)[i][3] == -1)
			{
				continue;
			}
			else
			{
				temp_index1 = (hierarchy)[i][3];

			}
			if ((hierarchy)[temp_index1][3] == -1)
			{
				continue;
			}
			else
			{
				temp_index2 = (hierarchy)[temp_index1][3];
			}
			if ((hierarchy)[temp_index2][3] == -1)
			{
				continue;
			}
			else
			{
				temp_index3 = (hierarchy)[temp_index2][3];
				index in;
				in.a1 = i;
				in.a2 = temp_index1;
				in.a3 = temp_index2;
				in.a4 = temp_index3;
				vin.push_back(in);
			}
		}


		//std::cout << "construct vin over: " << vin.size() << std::endl;
		int count = 0;
		for (auto it = vin.begin(); it != vin.end();)
		{
			cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 0, 0), FILLED, 8);
			it++;
		}
		//std::cout << "total count is " << count << std::endl;
		std::string win_name4("search_contours");
		//cv::namedWindow(win_name4);
		//cv::imshow(win_name4, draw1);
		//cv::waitKey(0);
#else

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
				cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), FILLED, 8);
				it++;
			}

		}
#endif

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

		auto end_time = std::chrono::system_clock::now();//-----------------------
		std::cout << "time duration is " << std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count() << "ms" << std::endl;

		std::cout << "mc size is : " << mc.size() << std::endl;
		cv::Mat drawing = cv::Mat::zeros(src.size(), CV_8UC3);
		for (int i = 0; i < target_contours.size(); i++)
		{
			cv::drawContours(drawing, target_contours, i, CV_RGB(255, 255, 255), -1, 8);
			cv::circle(drawing, mc[i], 4, color, -1, 8, 0);
			cv::line(drawing, mc[i % mc.size()], mc[(i + 1) % mc.size()], color);
		}
		std::string win_name5("Contours");
		cv::namedWindow(win_name5, WINDOW_AUTOSIZE);
		cv::imshow(win_name5, drawing);
		cv::waitKey(0);


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

		int d_w = 900;
		int d_h = 480;

		cv::Point2f dst_points[] = { cv::Point2f(50,50),cv::Point2f(50,50 + d_h),cv::Point2f(50 + d_w,50 + d_h),cv::Point2f(50 + d_w,50) };

		cv::Mat trans_matrix = cv::getPerspectiveTransform(src_points, dst_points);
		cv::Mat trans_pic = cv::Mat::zeros(cv::Size(1920, 1200), CV_8UC3);

		cv::warpPerspective(src, trans_pic, trans_matrix, cv::Size(1920, 1200), cv::INTER_LINEAR);
		cv::circle(trans_pic, cv::Point2f(mc[0].x + d_w, mc[0].y + d_h), 4, color, -1, 8, 0);

		std::string win_name8("after_matrix_trans");

		cv::namedWindow(win_name8, WINDOW_AUTOSIZE);
		cv::imshow(win_name8, trans_pic);
		cv::waitKey(0);

		cv::Mat dst;
		getRectSubPix(trans_pic, cv::Size(1024, 600), cv::Point2f(512, 300), dst);

		//cv::line(dst, cv::Point(80, 80), cv::Point(900, 80), cv::Scalar(255, 0, 0));
		//cv::line(dst, cv::Point(80, 500), cv::Point(900, 500), cv::Scalar(255, 0, 0));
		cv::circle(dst, cv::Point(50, 50), 2, color);
		cv::circle(dst, cv::Point(50, 50 + 480), 2, color);
		cv::circle(dst, cv::Point(50 + 900, 50), 2, color);
		cv::circle(dst, cv::Point(50 + 900, 50 + 480), 2, color);
		std::string win_name9("trans dst");
		cv::namedWindow(win_name9, WINDOW_AUTOSIZE);
		cv::imshow(win_name9, dst);
		cv::imwrite("dst_black_hu.png", dst);
		cv::waitKey(0);




		cv::destroyAllWindows();
		//std::this_thread::sleep_for(std::chrono::seconds(10));
	}
	return 0;
}



void image_read_data_demo()
{
	Mat src = imread("dst_black_hu.png");
	std::vector<Point> pos;


	for (int sy = 95; sy < 480 + 15; sy += 40)
	{
		for (int sx = 95; sx < 890 + 15 - 40; sx += 40)
		{
			pos.push_back(Point(sx, sy));
		}
	}

	printf("src -< channles = %d \n", src.channels());
	std::vector<int> color_b;
	std::vector<int> color_g;
	std::vector<int> color_r;
	std::vector<int> color_rgb;
	printf("pos size = %d \n", pos.size());

	for (auto it = pos.begin(); it != pos.end(); it++)
	{
		int b = src.at<Vec3b>(it->y, it->x)[0];
		int g = src.at<Vec3b>(it->y, it->x)[1];
		int r = src.at<Vec3b>(it->y, it->x)[2];
		if ((it - pos.begin()) % 20 == 0)
			printf("\n");
		printf("(%3d,%3d,%3d)\t", b, g, r);

		if (b >= 0 && b <= 64)
		{
			b = 0;
		}
		else if (b <= 128)
		{
			b = 1;
		}
		else if (b <= 192)
		{
			b = 2;
		}
		else
		{
			b = 3;
		}

		if (g >= 0 && g <= 64)
		{
			g = 0;
		}
		else if (g <= 128)
		{
			g = 1;
		}
		else if (g <= 192)
		{
			g = 2;
		}
		else
		{
			g = 3;
		}

		if (r >= 0 && r <= 64)
		{
			r = 0;
		}
		else if (r <= 128)
		{
			r = 1;
		}
		else if (r <= 192)
		{
			r = 2;
		}
		else
		{
			r = 3;
		}

		color_b.push_back(b);
		color_g.push_back(g);
		color_r.push_back(r);
	}
	printf("\n");

	std::string file_b;
	std::string file_g;
	std::string file_r;

	std::string temp_str_b;
	std::string temp_str_g;
	std::string temp_str_r;

	unsigned char r_byte;
	unsigned char g_byte;
	unsigned char b_byte;

	for (int i = 0; i <= color_b.size() - 4; i += 4)
	{
		b_byte = (color_b.at(i) * 4 + color_b.at(i + 1)) * 16 + color_b.at(i + 2) * 4 + color_b.at(i + 3);
		g_byte = (color_g.at(i) * 4 + color_g.at(i + 1)) * 16 + color_g.at(i + 2) * 4 + color_g.at(i + 3);
		r_byte = (color_r.at(i) * 4 + color_r.at(i + 1)) * 16 + color_r.at(i + 2) * 4 + color_r.at(i + 3);

		temp_str_b.push_back(b_byte);
		temp_str_b.push_back(g_byte);
		temp_str_b.push_back(r_byte);

	}
	std::cout << "tempstr size is " << temp_str_b.size() << std::endl;

	for (auto it = temp_str_b.begin(); it != temp_str_b.end(); ++it)
	{
		if ((it - temp_str_b.begin()) % 15 == 0)
			printf("\n");
		printf("%02X\t", static_cast<unsigned char>(*it));
	}
	std::cout << std::endl;

}


#if 0

double capture_param_test_read_data_sigle(my_mat_t& test_capture_sigle)
{
	if (test_capture_sigle.dst.empty())
	{
		std::cout << "dst is empty" << std::endl;
		return -1;
	}
	std::vector<Point> pos;

	for (int sy = 95; sy < 480 + 15; sy += 40)
	{
		for (int sx = 95; sx < 890 + 15 - 40; sx += 40)
		{
			pos.push_back(Point(sx, sy));
		}
	}

	std::vector<int> sum_sigle_mat;

	std::vector<double> diff_value;


	int sum2 = 0;
	for (auto pos_it = pos.begin(); pos_it != pos.end(); pos_it++)
	{
		int b = test_capture_sigle.dst.at<Vec3b>(pos_it->y, pos_it->x)[0];
		int g = test_capture_sigle.dst.at<Vec3b>(pos_it->y, pos_it->x)[1];
		int r = test_capture_sigle.dst.at<Vec3b>(pos_it->y, pos_it->x)[2];

		b = b - 32;
		int b2 = b * b;
		g = g - 32;
		int g2 = g * g;
		r = r - 32;
		int r2 = r * r;

		sum2 += b2 + g2 + r2;
	}
	test_capture_sigle.Difference_value = sum2 / pos.size();

	return test_capture_sigle.Difference_value;
}


int capture_param_test_read_data(std::vector<my_mat_t>& test_capture, my_mat_t& dst_param)
{
	std::vector<Point> pos;

	for (int sy = 95; sy < 480 + 15; sy += 40)
	{
		for (int sx = 95; sx < 890 + 15 - 40; sx += 40)
		{
			pos.push_back(Point(sx, sy));
		}
	}

	std::vector<int> sum_sigle_mat;
	std::vector<int> color_g;
	std::vector<int> color_r;
	std::vector<int> color_rgb;
	std::vector<double> diff_value; 


	for (auto it = test_capture.begin(); it != test_capture.end(); ++it)
	{
		int sum2 = 0;
		for (auto pos_it = pos.begin(); pos_it != pos.end(); pos_it++)
		{
			int b = it->dst.at<Vec3b>(pos_it->y, pos_it->x)[0];
			int g = it->dst.at<Vec3b>(pos_it->y, pos_it->x)[1];
			int r = it->dst.at<Vec3b>(pos_it->y, pos_it->x)[2];

			b = b - 32;
			int b2 = b * b;
			g = g - 32;
			int g2 = g * g;
			r = r - 32;
			int r2 = r * r;

			sum2 += b2 + g2 + r2;
		}
		it->Difference_value = sum2 / pos.size();
	}

	auto cmp = [](my_mat_t &a, my_mat_t &b) {return a.Difference_value < b.Difference_value; };

	std::sort(test_capture.begin(), test_capture.end(), cmp);
	
	dst_param = test_capture[0];

	return 0;
}

int capture_param_test_process_sigle(my_mat_t &test_capture_sigle)
{

	if (test_capture_sigle.src.empty())
	{
		std::cout << test_capture_sigle.name << "is empty" << std::endl;
		return -1;
	}
	else
	{
		cv::Mat src_gray;
		//转灰度图
		cv::cvtColor(test_capture_sigle.src, src_gray, cv::COLOR_BGR2GRAY);
		//平滑处理
		cv::blur(src_gray, src_gray, cv::Size(3, 3));
		//直方图均衡化
		cv::equalizeHist(src_gray, src_gray);

		cv::Mat src_threshold;
		cv::threshold(src_gray, src_threshold, 100, 255, cv::THRESH_BINARY);
		cv::Scalar color(1, 1, 255);
		std::vector<std::vector<cv::Point>> contours;
		std::vector<cv::Vec4i> hierarchy;
		cv::Mat draw1 = cv::Mat::zeros(test_capture_sigle.src.size(), CV_8UC3);
		cv::Mat draw2 = cv::Mat::zeros(test_capture_sigle.src.size(), CV_8UC3);

		findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, cv::Point(0, 0));

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

			double len2 = cv::arcLength(contours_out2, 1);


			if (abs(len1 / len2 - 2) > 1)
			{
				it = vin.erase(it);
			}
			else
			{
				cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), FILLED, 8);
				it++;
			}

		}
		if (vin.size() != 4)
		{
			std::cout << test_capture_sigle.name << "contrust vin not is 4" << std::endl;
			//my_show_pic("fail image", test_capture_sigle.src);
			return -1;
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
		}

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

		int d_w = 900;
		int d_h = 480;

		cv::Point2f dst_points[] = { cv::Point2f(50,50),cv::Point2f(50,50 + d_h),cv::Point2f(50 + d_w,50 + d_h),cv::Point2f(50 + d_w,50) };

		cv::Mat trans_matrix = cv::getPerspectiveTransform(src_points, dst_points);
		cv::Mat trans_pic = cv::Mat::zeros(cv::Size(1920, 1200), CV_8UC3);

		cv::warpPerspective(test_capture_sigle.src, trans_pic, trans_matrix, cv::Size(1920, 1200), cv::INTER_LINEAR);
		cv::circle(trans_pic, cv::Point2f(mc[0].x + d_w, mc[0].y + d_h), 4, color, -1, 8, 0);

		getRectSubPix(trans_pic, cv::Size(1024, 600), cv::Point2f(512, 300), test_capture_sigle.dst);

	}
	return 0;
}

int capture_param_test_process(std::vector<my_mat_t>& test_capture)
{
	for (auto it = test_capture.begin(); it != test_capture.end(); ++it)
	{
		if (it->src.empty())
		{
			std::cout << it->name << "is empty" << std::endl;
			continue;
		}
		else
		{
			cv::Mat src_gray;
			//转灰度图
			cv::cvtColor(it->src, src_gray, cv::COLOR_BGR2GRAY);
			//平滑处理
			cv::blur(src_gray, src_gray, cv::Size(3, 3));
			//直方图均衡化
			cv::equalizeHist(src_gray, src_gray);

			cv::Mat src_threshold;
			cv::threshold(src_gray, src_threshold, 100, 255, cv::THRESH_BINARY);
			cv::Scalar color(1, 1, 255);
			std::vector<std::vector<cv::Point>> contours;
			std::vector<cv::Vec4i> hierarchy;
			cv::Mat draw1 = cv::Mat::zeros(it->src.size(), CV_8UC3);
			cv::Mat draw2 = cv::Mat::zeros(it->src.size(), CV_8UC3);

			findContours(src_threshold, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, cv::Point(0, 0));

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

				double len2 = cv::arcLength(contours_out2, 1);


				if (abs(len1 / len2 - 2) > 1)
				{
					it = vin.erase(it);
				}
				else
				{
					cv::drawContours(draw1, contours, it->a1, CV_RGB(255, 255, 255), FILLED, 8);
					it++;
				}

			}
			if (vin.size() != 4)
			{
				std::cout << it->name << "contrust vin not is 4" << std::endl;
				continue;
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
			}

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

			int d_w = 900;
			int d_h = 480;

			cv::Point2f dst_points[] = { cv::Point2f(50,50),cv::Point2f(50,50 + d_h),cv::Point2f(50 + d_w,50 + d_h),cv::Point2f(50 + d_w,50) };

			cv::Mat trans_matrix = cv::getPerspectiveTransform(src_points, dst_points);
			cv::Mat trans_pic = cv::Mat::zeros(cv::Size(1920, 1200), CV_8UC3);

			cv::warpPerspective(it->src, trans_pic, trans_matrix, cv::Size(1920, 1200), cv::INTER_LINEAR);
			cv::circle(trans_pic, cv::Point2f(mc[0].x + d_w, mc[0].y + d_h), 4, color, -1, 8, 0);

			getRectSubPix(trans_pic, cv::Size(1024, 600), cv::Point2f(512, 300), it->dst);

		}
	}
	return 0
}
#endif
