#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>


class SudokuRead{
public:
	void cornerHarris_demo(int, void*, cv::Mat src, cv::Mat src_gray);
	void drawLine(cv::Vec2f line, cv::Mat &img, cv::Scalar rgb);
	void mergeRelatedLines(std::vector<cv::Vec2f> *lines, cv::Mat &img);
	cv::String inttostr(int input);
	int go();
};