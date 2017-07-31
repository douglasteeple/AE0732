/*
 * Class ImageAnalysisService - performs various image analysis services.
 *
 *  Created by Douglas Teeple on 7/31/17.
 *  Copyright © 2017 Douglas Teeple. All rights reserved.
*/

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "ImageAnalysisService.hpp"

std::vector<cv::Point> ImageAnalysisService::FIND_REGION(const cv::Mat &image, int x, int y, int distance, int *hue) {
    std::vector<cv::Point> pointvector;
    if (image.empty()) {                      // Check for invalid input
        return pointvector;
    }
    // The algorithm classifies by closest color, the simplest way to do this is to convert
    // to hsv (hue saturation value) and compare hues. Note that hue values are halved, so are in the range 1-179
    // Approx. hue values: R=360 G=120 Y=60 B=240
    cv::Mat hsv_image;
    cvtColor(image, hsv_image, CV_RGB2HSV);
    cv::Vec3b region_intensity = hsv_image.at<cv::Vec3b>(x, y);
    int the_hue = region_intensity.val[0];
    // return the hue if desired
    if (hue != nullptr) {
        *hue = the_hue*2;   // double to get 0-360 degrees
    }
    for (int i = 0; i < hsv_image.rows; ++i) {
        for (int j = 0; j < hsv_image.cols; ++j) {
            cv::Vec3b intensity = hsv_image.at<cv::Vec3b>(i, j);
            if (abs(intensity.val[0]-the_hue) < distance) {
                std::cout << i << " " << j << " h= " << (int)intensity.val[0] << " s= " << (int)intensity.val[1] << " v= "<< (int)intensity.val[2] << std::endl;
                pointvector.push_back(cv::Point(i,j));
            }
        }
    }
    return pointvector;
}
std::vector<cv::Point> ImageAnalysisService::FIND_PERIMETER(const std::vector<cv::Point> &region) {
    std::vector<cv::Point> pointvector;
    return pointvector;
}
void ImageAnalysisService::DISPLAY_IMAGE(const cv::Mat &image, std::string const &win_name) {
    namedWindow(win_name, cv::WINDOW_AUTOSIZE);
    cvtColor(image, image, cv::COLOR_RGB2BGR);  // opencv displays BGR, we use RGB internally
    imshow(win_name, image);
}
void ImageAnalysisService::DISPLAY_PIXELS(const std::vector<cv::Point> &region, std::string const &win_name) {
    int maxrows = 0;
    int maxcols = 0;
    // find the dimensions of the region
    for (int i=0; i<region.size(); i++) {
        if (region[i].x > maxrows)
            maxrows = region[i].x;
        if (region[i].y > maxrows)
            maxcols = region[i].y;
    }
    // create an image of that size, initialize to all zeros
    cv::Mat image = cv::Mat::zeros(maxrows, maxcols, CV_8UC1);
    // assign white to pixels in region
    for (int i=0; i<region.size(); i++) {
        image.at<uchar>(region[i].x, region[i].y, 0) = 255;
    }
    // and display
    namedWindow(win_name, cv::WINDOW_AUTOSIZE);
    imshow(win_name, image);
}

void ImageAnalysisService::SAVE_PIXELS(const std::vector<cv::Point> &region, std::string const &file_name) {
    int maxrows = 0;
    int maxcols = 0;
    // find the dimensions of the region
    for (int i=0; i<region.size(); i++) {
        if (region[i].x > maxrows)
        maxrows = region[i].x;
        if (region[i].y > maxrows)
        maxcols = region[i].y;
    }
    // create an image of that size, initialize to all zeros
    cv::Mat image = cv::Mat::zeros(maxrows, maxcols, CV_8UC1);
    // assign white to pixels in region
    for (int i=0; i<region.size(); i++) {
        image.at<uchar>(region[i].x, region[i].y, 0) = 255;
    }
    imwrite(file_name, image);
}

void ImageAnalysisService::SAVE_IMAGE(const cv::Mat &image, std::string const &file_name) {
    cvtColor(image, image, cv::COLOR_RGB2BGR);  // opencv reads/writes BGR, we use RGB internally
    imwrite(file_name, image);
}
