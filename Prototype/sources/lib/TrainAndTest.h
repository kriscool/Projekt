#pragma once
#include "SudokuMatrix.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/ml/ml.hpp>

#include<iostream>
#include<sstream>
#include<string>
const int MIN_CONTOUR_AREA = 100;
const int RESIZED_IMAGE_WIDTH = 20;
const int RESIZED_IMAGE_HEIGHT = 30;

class ContourWithData {
public:
	std::vector<cv::Point> ptContour;
	cv::Rect boundingRect;
	float fltArea;
	SudokuMatrix getScan();
	bool checkIfContourIsValid();
	static bool sortByBoundingRectXPosition(const ContourWithData& cwdLeft, const ContourWithData& cwdRight);
private:
	int read(int a);
};