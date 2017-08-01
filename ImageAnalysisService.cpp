/*
 * Class ImageAnalysisService - performs various image analysis services.
 *
 *  Created by Douglas Teeple on 7/31/17.
 *  Copyright © 2017 Douglas Teeple. All rights reserved.
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "ImageAnalysisService.hpp"

// TODO: Implement exceptions

/*
 *  FIND_REGION accepts an RGB image, an (X, Y) pixel location, and a distance parameter to
 *  control a greedy style algorithm that "flood fills" the nearby pixels in order to find
 *  a contiguous patch of pixels that are similar in color. The return value is a vector of
 *  cv::Points. The RGB image is converted to HSV to easily select by color (H). The maximum
 *  distance from the color at point x,y is given as a parameter. The hue at the x,y point
 *  is optionally returned in the "*hue" argument. Returns empty vector if x or y outside
 *  image range.
 */
std::vector<cv::Point> ImageAnalysisService::FIND_REGION(const cv::Mat &image, int x, int y, int distance, int *hue) {
    std::vector<cv::Point> pointvector;
    if (!image.empty()) {                      // Check for invalid input
        cv::Size s = image.size();
        int rows = s.height;
        int cols = s.width;
        // The algorithm classifies by closest color, the simplest way to do this is to convert
        // to hsv (hue saturation value) and compare hues. Note that hue values are halved, so are in the range 1-179
        // Approx. hue values: R=360 G=120 Y=60 B=240
        if (x >= 0 && x < cols && y >= 0 && y < rows) {
            cv::Mat hsv_image;
            cvtColor(image, hsv_image, CV_RGB2HSV);
            cv::Vec3b region_intensity = hsv_image.at<cv::Vec3b>(y, x);
            int the_hue = region_intensity.val[0];
            // return the hue if desired
            if (hue != nullptr) {
                *hue = the_hue*2;   // double to get 0-360 degrees
            }
            for (int i = 0; i < hsv_image.rows; ++i) {
                for (int j = 0; j < hsv_image.cols; ++j) {
                    cv::Vec3b intensity = hsv_image.at<cv::Vec3b>(i, j);
                    if (abs(intensity.val[0]-the_hue) < distance) {
                        pointvector.push_back(cv::Point(j,i));
                    }
                }
            }
        }
    }
    return pointvector;
}

/*
 *  FIND_PERIMETER accepts the output of FIND_REGION and outputs contiguous pixels that
 *  border the region. These pixels should be a subset of pixels returned by FIND_REGION.
 */
std::vector<cv::Point> ImageAnalysisService::FIND_PERIMETER(const std::vector<cv::Point> &region) {
    std::vector<cv::Point> pointvector;
    int maxrows = 0;
    int maxcols = 0;
    // find the dimensions of the region
    if (FIND_REGION_SIZE(region, &maxrows, &maxcols)) {
        // create an image of that size, initialize to all zeros
        cv::Mat image = cv::Mat::zeros(maxrows, maxcols, CV_8UC1);
        // assign white to pixels in region
        for (int i=0; i<region.size(); i++) {
            image.at<uchar>(region[i].y, region[i].x, 0) = 255;
        }
        // now scan that image, if all neighbors are 255 then exclude from the output vector
        for (int i = 1; i < image.rows-1; ++i) {
            for (int j = 1; j < image.cols-1; ++j) {
                uchar img_val = image.at<uchar>(i, j, 0);
                if (image.at<uchar>(i-1, j-1, 0) == img_val &&
                    image.at<uchar>(i+1, j-1, 0) == img_val &&
                    image.at<uchar>(i-1, j+1, 0) == img_val &&
                    image.at<uchar>(i+1, j+1, 0) == img_val) {
                    // exclude
                } else {
                    pointvector.push_back(cv::Point(j,i));
                }
            }
        }
    }
    return pointvector;
}

/*
 *  DISPLAY_IMAGE provides a method for displaying loaded RGB images.
 */
void ImageAnalysisService::DISPLAY_IMAGE(const cv::Mat &image, std::string const &win_name) {
    cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
    cvtColor(image, image, cv::COLOR_RGB2BGR);  // opencv displays BGR, we use RGB internally
    cv::imshow(win_name, image);
    cv::waitKey(1000);
    cv::destroyWindow(win_name);
}

/*
 *  DISPLAY_PIXELS provides a method for displaying an image representation of the
 *  results from the above FIND_* operators.
 */
void ImageAnalysisService::DISPLAY_PIXELS(const std::vector<cv::Point> &region, std::string const &win_name) {
    int maxrows = 0;
    int maxcols = 0;
    // find the dimensions of the region
    if (FIND_REGION_SIZE(region, &maxrows, &maxcols)) {
        // create an image of that size, initialize to all zeros
        cv::Mat image = cv::Mat::zeros(maxrows, maxcols, CV_8UC1);
        // assign white to pixels in region
        for (int i=0; i<region.size(); i++) {
            image.at<uchar>(region[i].y, region[i].x, 0) = 255;
        }
        // and display
        cv::namedWindow(win_name, cv::WINDOW_AUTOSIZE);
        cv::imshow(win_name, image);
        cv::waitKey(1000);
        cv::destroyWindow(win_name);
    } else {
        // throw exception
    }
}

/*
 *  SAVE_PIXELS accepts the vector output from FIND_* and saves the image to a file.
 */
void ImageAnalysisService::SAVE_PIXELS(const std::vector<cv::Point> &region, std::string const &file_name) {
    int maxrows = 0;
    int maxcols = 0;
    // find the dimensions of the region
    if (FIND_REGION_SIZE(region, &maxrows, &maxcols)) {
        // create an image of that size, initialize to all zeros
        cv::Mat image = cv::Mat::zeros(maxrows, maxcols, CV_8UC1);
        // assign white to pixels in region
        for (int i=0; i<region.size(); i++) {
            image.at<uchar>(region[i].y, region[i].x, 0) = 255;
        }
        imwrite(file_name, image);
    } else {
        // throw exception
    }
}

/*
 *  SAVE_IMAGE saves the image to a file.
 */
void ImageAnalysisService::SAVE_IMAGE(const cv::Mat &image, std::string const &file_name) {
    imwrite(file_name, image);
}
