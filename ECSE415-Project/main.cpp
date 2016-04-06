#include <iostream>

#include <opencv2/opencv.hpp>

int main() {
	std::cout << "Hello World" << std::endl;
	cv::Mat img = cv::imread("test.png");
	imshow("test", img);
	cv::waitKey();
}