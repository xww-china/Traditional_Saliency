#include "LC1.h"
#include<iostream>




void LC1::calculateSaliencyMap1(Mat* srcimage, Mat* desimage) {
	Mat image;
	if ((*srcimage).channels() == 3) {
		cvtColor(*srcimage, image, COLOR_RGB2GRAY);
	}
	else
		image = *srcimage;

	double f[256], s[256];
	memset(f, 0, 256 * sizeof(double));
	memset(s, 0, 256 * sizeof(double));

	/*
	知识补充
	cv::Mat image = cv::Mat(400, 600, CV_8UC1);  //定义了一个Mat变量image。
	uchar * data00 = image.ptr<uchar>(0);  //data00是指向image第一行第一个元素的指针。
	uchar * data10 = image.ptr<uchar>(1);  //data10是指向image第二行第一个元素的指针。
	uchar * data01 = image.ptr<uchar>(0)[1];//data01是指向image第一行第二个元素的指针。
	*/
	//1:【计算图像的直方图】
	//data[c]即表打第r行第c列的像素值
	for (int r = 0; r < image.rows; r++) {
		uchar* data = image.ptr<uchar>(r);
		for (int c = 0; c < image.cols; c++) {
			f[data[c]] = f[data[c]] + 1;
		}
	}

	//2:【遍历图像计算特征值距离矩阵D】

	double s_min = DBL_MAX, s_max = 0;
	for (int i = 0; i < 256; i++) {


		for (int j = 0; j < 256; j++) {
			s[i] += abs(i - j) * abs(i - j) * f[j];
		}
		if (s[i] > s_max) s_max = s[i];
		if (s[i] < s_min) s_min = s[i];
	}

	//3:【将显著特征值归一化到0-255】
	for (int i = 0; i < 256; i++) {
		s[i] = (s[i] - s_min) / (s_max - s_min) * 255;
	}

	//4:【为每个像素分配显著值，（i，j）是什么灰度级就赋予它相应灰度级得显著值，得到显著图】
	Mat temp(image.size(), CV_64F);

	for (int r = 0; r < image.rows; r++) {
		uchar* data = image.ptr<uchar>(r);
		double* sal = temp.ptr<double>(r);
		for (int c = 0; c < image.cols; c++) {
			sal[c] = s[data[c]];
		}
	}

	temp.convertTo(*desimage, CV_8U, 1, 0);

}

int main() {
	Mat srcImage, desImage;    //destination image
	//srcImage = imread("F:\\学习工作\\学校\\C++\\images\\2.jpg",3);
	
	srcImage = imread("./images/1.jpg", 3);
	
	if (srcImage.empty()) {
		std::cout << "未找到图片路径";
	}
	else{
    imshow("原图",srcImage);
    //std::cout << "height: " << srcImage.rows << " width: " << srcImage.cols<<'\n' << std::endl;
	cvtColor(srcImage, srcImage, COLOR_RGB2GRAY);
	imshow("灰度图", srcImage);

	LC1 lc;

	lc.calculateSaliencyMap1(&srcImage,&desImage);
	imshow("LC算法显著性图",desImage);


	}

	waitKey(0);
	return 0;
}

