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
	֪ʶ����
	cv::Mat image = cv::Mat(400, 600, CV_8UC1);  //������һ��Mat����image��
	uchar * data00 = image.ptr<uchar>(0);  //data00��ָ��image��һ�е�һ��Ԫ�ص�ָ�롣
	uchar * data10 = image.ptr<uchar>(1);  //data10��ָ��image�ڶ��е�һ��Ԫ�ص�ָ�롣
	uchar * data01 = image.ptr<uchar>(0)[1];//data01��ָ��image��һ�еڶ���Ԫ�ص�ָ�롣
	*/
	//1:������ͼ���ֱ��ͼ��
	//data[c]������r�е�c�е�����ֵ
	for (int r = 0; r < image.rows; r++) {
		uchar* data = image.ptr<uchar>(r);
		for (int c = 0; c < image.cols; c++) {
			f[data[c]] = f[data[c]] + 1;
		}
	}

	//2:������ͼ���������ֵ�������D��

	double s_min = DBL_MAX, s_max = 0;
	for (int i = 0; i < 256; i++) {


		for (int j = 0; j < 256; j++) {
			s[i] += abs(i - j) * abs(i - j) * f[j];
		}
		if (s[i] > s_max) s_max = s[i];
		if (s[i] < s_min) s_min = s[i];
	}

	//3:������������ֵ��һ����0-255��
	for (int i = 0; i < 256; i++) {
		s[i] = (s[i] - s_min) / (s_max - s_min) * 255;
	}

	//4:��Ϊÿ�����ط�������ֵ����i��j����ʲô�Ҷȼ��͸�������Ӧ�Ҷȼ�������ֵ���õ�����ͼ��
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
	//srcImage = imread("F:\\ѧϰ����\\ѧУ\\C++\\images\\2.jpg",3);
	
	srcImage = imread("./images/1.jpg", 3);
	
	if (srcImage.empty()) {
		std::cout << "δ�ҵ�ͼƬ·��";
	}
	else{
    imshow("ԭͼ",srcImage);
    //std::cout << "height: " << srcImage.rows << " width: " << srcImage.cols<<'\n' << std::endl;
	cvtColor(srcImage, srcImage, COLOR_RGB2GRAY);
	imshow("�Ҷ�ͼ", srcImage);

	LC1 lc;

	lc.calculateSaliencyMap1(&srcImage,&desImage);
	imshow("LC�㷨������ͼ",desImage);


	}

	waitKey(0);
	return 0;
}

