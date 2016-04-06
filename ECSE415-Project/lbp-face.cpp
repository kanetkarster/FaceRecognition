#include "lbp-face.h"

#include <opencv2/opencv.hpp>

void get_lbp_representation(cv::Mat &const img , cv::Mat &lbp);
void compute_lbp_histogram(cv::Mat &const lbp, int grid_size, cv::Mat lbp_histogram);

void lbp_train() {
	cv::Mat img = cv::imread("QMUL/AdamBGrey/AdamB_060_090.ras");
	cv::Mat lbp;

	get_lbp_representation(img, lbp);

	cv::imshow("lbp version", lbp);
	cv::waitKey();
}

void get_lbp_representation(cv::Mat &const img , cv::Mat &lbp) {
	/* offset by two to avoid first and last row and column */
	lbp = cv::Mat::zeros(img.rows-2, img.cols-2, CV_8UC1);
	
	/* fill lbp matrix */
	for (int row=1; row<img.rows-1; row++) {
		for (int col=1; col<img.cols-1; col++) {
			/* calculate LBP descriptor */

			unsigned char center = img.at<unsigned char>(row, col);
			unsigned char binary_pattern = 0;
			/* Grid of neighboring pixels
			 *	 _ _ _ _
			 *	| 1 2 3 |
			 *	| 8 * 4 |
			 *	| 7 6 5 |
			 *   - - - -
			 */
			/* set bits in accordance with above grid */
			binary_pattern |= (img.at<unsigned char>(row-1, col-1) > center) << 7;	// 1
			binary_pattern |= (img.at<unsigned char>(row-1, col) > center) << 6;		// 2
			binary_pattern |= (img.at<unsigned char>(row-1, col+1) > center) << 5;	// 3
			binary_pattern |= (img.at<unsigned char>(row, col+1) > center) << 4;		// 4
			binary_pattern |= (img.at<unsigned char>(row+1, col+1) > center) << 3;	// 5
			binary_pattern |= (img.at<unsigned char>(row+1, col) > center) << 2;		// 6
			binary_pattern |= (img.at<unsigned char>(row+1, col-1) > center) << 1;	// 7
			binary_pattern |= (img.at<unsigned char>(row, col-1) > center) << 0;		// 8

			/* set data in output Matrix */
			lbp.at<unsigned char>(row-1, col-1) = binary_pattern;
		}
	}
}

void compute_lbp_histogram(cv::Mat &const lbp, int grid_size, cv::Mat lbp_histogram) {
	std::vector<cv::Mat> sections;

	/* Get number of pixels between each grid box */
	int HEIGHT = lbp.rows;
	int WIDTH = lbp.cols;

	int delta_height = HEIGHT / grid_size;
	int delta_width = WIDTH / grid_size;

	/* Seperate Grid into a Vector of Matricies */
	for (int row=0; row<grid_size; row++) {
		for (int col=0; col<grid_size; col++) {
			cv::Rect roi(col * delta_width, row * delta_height, delta_width, delta_height);
			sections.push_back(cv::Mat(lbp, roi));
		}
	}

}
