#include "lbp-face.h"

#include <opencv2/opencv.hpp>

void get_lbp_representation(cv::Mat &const img , cv::Mat &lbp);

void lbp_train() {

}

void get_lbp_representation(cv::Mat &const img , cv::Mat &lbp) {
	/* offset by two to avoid first and last row and column */
	lbp = cv::Mat::zeros(img.rows-2, img.cols-2, CV_8UC1);
	
	/* fill lbp matrix */
	for (int row=1; row<img.rows-1; row++) {
		for (int col=1; col<img.cols-1; col++) {
			/* calculate LBP descriptor */

			int center = img.at<int>(row, col);
			unsigned char binary_pattern = 0;
			/* Grid of neighboring pixels
			 *	 _ _ _ _
			 *	| 1 2 3 |
			 *	| 8 * 4 |
			 *	| 7 6 5 |
			 *   - - - -
			 */
			/* set bits in accordance with above grid */
			binary_pattern |= (img.at<int>(row-1, col-1) > center) << 7;	// 1
			binary_pattern |= (img.at<int>(row-1, col) > center) << 6;		// 2
			binary_pattern |= (img.at<int>(row-1, col+1) > center) << 5;	// 3
			binary_pattern |= (img.at<int>(row, col+1) > center) << 4;		// 4
			binary_pattern |= (img.at<int>(row+1, col+1) > center) << 3;	// 5
			binary_pattern |= (img.at<int>(row+1, col) > center) << 2;		// 6
			binary_pattern |= (img.at<int>(row+1, col-1) > center) << 1;	// 7
			binary_pattern |= (img.at<int>(row, col-1) > center) << 0;		// 8

			/* set data in output Matrix */
			lbp.at<unsigned char>(row, col) = binary_pattern;
		}
	}
}
