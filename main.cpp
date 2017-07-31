//
//  main.cpp - test driver for
//  AeolusImageAnalysis Service
//
//  Created by Douglas Teeple on 7/31/17.
//  Copyright © 2017 Douglas Teeple. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include "ImageAnalysisService.hpp"

using namespace cv;

/*
 * TODO: test these points:
 *
 * test1.png
 * (58,147)
 * (19,33)
 * (58,100)
 * (100,100)
 * (122,60)
 *
 * test2.png
 * (90,140)
 * (58,100)
 * (100,100)
 * (164,72)
 * (122,98)
 *
 * test3.png
 * (58,100)
 * (100,100)
 * (156,103)
 *
 * test4.jpg pick your own points but, suggested interesting points:
 * (416,486)
 * (1510,640)
 * (1590,1940)
 * (2200,600)
 * (3300,1420) 
 *
 */

int main(int argc, char **argv) {
    
    if (argc < 5) {
        printf("usage: AeolusImageAnalysis <Image_Path> <Output_Path> x y distance\n");
        return -1;
    }
    
    
    Mat image = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    
    if (!image.data) {
        printf("Invalid image: %s\n", argv[1]);
        return -1;
    }
    
    int x = atoi(argv[3]);
    int y = atoi(argv[4]);
    int hue = 0;
    int distance = (argc==6?atoi(argv[5]):20);
    cv::Size s = image.size();
    int rows = s.height;
    int cols = s.width;
    unsigned long image_size = rows * cols;
    
    if (x > cols || y > rows) {
        printf("Invalid x,t coordinates: must be in range 0-%d, 0-%d\n", rows, cols);
        return -1;
    }
    
    cvtColor(image, image, COLOR_BGR2RGB);  // opencv reads BGR, we use RGB
    
    ImageAnalysisService *service = new ImageAnalysisService;
    
    service->DISPLAY_IMAGE(image, argv[1]);
    
    std::vector<cv::Point> region = service->FIND_REGION(image, x, y, distance, &hue);
    
    std::cout << "Image size  " << rows << " x " << cols << " = " <<  image_size << " pixels" << std::endl;
    std::cout << "Found " << region.size() << " pixels of color " << hue << " within range " << distance << " about " << (((float)region.size()*100.0)/(float)image_size) << "%" << std::endl;
    
    service->DISPLAY_PIXELS(region, "region");
    service->SAVE_PIXELS(region, "region.png");
    
    std::vector<cv::Point> perimeter = service->FIND_PERIMETER(region);

    service->DISPLAY_PIXELS(perimeter, "perimeter");
    service->SAVE_PIXELS(perimeter, "perimeter.png");
   
    service->SAVE_IMAGE(image, argv[2]);
    
    return 0;
}
