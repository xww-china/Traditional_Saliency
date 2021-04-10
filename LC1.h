#define _CRT_SECURE_NO_WARNINGS
#include "opencv2/core/core.hpp" 
#include<typeinfo>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
class LC1
{
public:
	LC1()
	{
	}

	~LC1()
	{
	}

public:
	void calculateSaliencyMap1(Mat* src, Mat* dst);

};

#pragma once
