#include <opencv2/opencv.hpp> 
#include <opencv2/nonfree/nonfree.hpp> 

double computePixelLBP(const cv::Mat input);
cv::Mat computeLBP(const cv::Mat input);
cv::Mat computeImageLBP(const cv::Mat input, int patchNumber);
cv::Mat getSpatialPyramidHistogram(const cv::Mat input, int levels);