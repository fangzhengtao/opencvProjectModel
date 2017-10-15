#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;
using namespace std;
int main()
{
	Mat img = imread("boy.png");
	int img_height = img.rows;
	int img_width = img.cols;
	vector<Point2f> corners(4);
	corners[0] = Point2f(0, 0);
	corners[1] = Point2f(img_width - 1, 0);
	corners[2] = Point2f(0, img_height - 1);
	corners[3] = Point2f(img_width - 1, img_height - 1);
	vector<Point2f> corners_trans(4);
	corners_trans[0] = Point2f(50, 50);
	corners_trans[1] = Point2f(img_width - 50, 50);
	corners_trans[2] = Point2f(0, img_height - 1);
	corners_trans[3] = Point2f(img_width - 1, img_height -1);

	Mat transform = getPerspectiveTransform(corners, corners_trans);
	cout << transform << endl;
	vector<Point2f> ponits, points_trans;
	for (int i = 0; i < img_height; i++) {
		for (int j = 0; j < img_width; j++) {
			ponits.push_back(Point2f(j, i));
		}
	}

	perspectiveTransform(ponits, points_trans, transform);
	Mat img_trans = Mat::zeros(img_height, img_width, CV_8UC3);
	int count = 0;
	for (int i = 0; i < img_height; i++) {
		uchar* p = img.ptr<uchar>(i);
		for (int j = 0; j < img_width; j++) {
			int y = points_trans[count].y;
			int x = points_trans[count].x;
			uchar* t = img_trans.ptr<uchar>(y);
			t[x * 3] = p[j * 3];
			t[x * 3 + 1] = p[j * 3 + 1];
			t[x * 3 + 2] = p[j * 3 + 2];
			count++;
		}
	}
	imwrite("boy_trans.png", img_trans);
	imshow("result", img_trans);
	waitKey();
	return 0;
}