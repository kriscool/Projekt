#pragma once
#include <opencv2/opencv.hpp>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

class SudokuRead{
public:
	void cornerHarris_demo(int, void*, Mat src, Mat src_gray);
	void drawLine(Vec2f line, Mat &img, Scalar rgb = CV_RGB(0, 0, 255));
	void mergeRelatedLines(vector<Vec2f> *lines, Mat &img);
	String inttostr(int input);
	int go();
};