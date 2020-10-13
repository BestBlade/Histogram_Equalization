#include <iostream>
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include"opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace std;
using namespace cv;

Mat histogram_equalization(Mat img) {
	Mat res(img.rows, img.cols, img.type());
	
	if (img.channels() == 1) {
		int nums[256] = { 0 };
		for (int x = 0; x < img.rows; x++) {
			for (int y = 0; y < img.cols; y++) {
				int val = img.at<uchar>(x, y);
				nums[val]++;
			}
		}
		//������ʷֲ�
		float porb[256] = { 0 };
		for (int n = 0; n < 256; n++) {
			porb[n] = nums[n] / float(img.rows * img.cols);
		}
		//�����ۼƷֲ�
		float cdf[256] = { 0 };
		for (int n = 0; n < 256; n++) {
			if (n == 0) {
				cdf[n] = porb[n];
			}
			else {
				cdf[n] = porb[n - 1] + cdf[n - 1];
			}
		}
		//�Ҷ�ӳ��
		for (int n = 0; n < 256; n++) {
			cdf[n] = uchar(255 * cdf[n] + 0.5);
		}
		//�ع�ͼƬ
		for (int x = 0; x < res.rows; x++) {
			for (int y = 0; y < res.cols; y++) {
				res.at<uchar>(x, y) = cdf[img.at<uchar>(x, y)];
			}
		}
	}
	else {
		//����bgr����ͨ���ֱ����
		for (int c = 0; c < img.channels(); c++) {
			int nums[256] = { 0 };
			for (int x = 0; x < img.rows; x++) {
				for (int y = 0; y < img.cols; y++) {
					int val = img.at<Vec3b>(x, y)[c];
					nums[val]++;
				}
			}
			//������ʷֲ�
			float porb[256] = { 0 };
			for (int n = 0; n < 256; n++) {
				porb[n] = nums[n] / float(img.rows * img.cols);
			}
			//�����ۼƷֲ�
			float cdf[256] = { 0 };
			for (int n = 0; n < 256; n++) {
				if (n == 0) {
					cdf[n] = porb[n];
				}
				else {
					cdf[n] = porb[n - 1] + cdf[n - 1];
				}
			}
			//�Ҷ�ӳ��
			for (int n = 0; n < 256; n++) {
				cdf[n] = uchar(255 * cdf[n] + 0.5);
			}
			//�ع�ͼƬ
			for (int x = 0; x < res.rows; x++) {
				for (int y = 0; y < res.cols; y++) {
					res.at<Vec3b>(x, y)[c] = cdf[img.at<Vec3b>(x, y)[c]];
				}
			}
		}
	}
	return res;
}

int main() {
	Mat img = imread("C://Users//Chrysanthemum//Desktop//1.png", 1);

	Mat res = histogram_equalization(img);
	//Mat res(img.rows, img.cols, img.type());

	imshow("origin pic", img);
	imshow("result pic", res);
	waitKey();
}