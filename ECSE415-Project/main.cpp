
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#include "lbp.h"

void main()
{
	//load image and set directory - just for testing
	const std::string folderName = "./QMUL/AdamBGrey/";
	const std::string filename = "AdamB_090_090.ras";

	cv::Mat inputImage;
	inputImage = cv::imread(folderName + filename, CV_LOAD_IMAGE_COLOR);

	imshow("original", inputImage);
	//convert to greyScale
	cv::cvtColor(inputImage, inputImage, CV_RGB2GRAY);


	//compute spatial pyramid histogram for number of level
	cv::Mat spatialHist = getSpatialPyramidHistogram(inputImage, 5);

	//wait to exit
	cv::waitKey(0);

}