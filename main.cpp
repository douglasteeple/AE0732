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

int main(int argc, char **argv) {
    
    if (argc < 4) {
        printf("usage: AeolusImageAnalysis <Image_Path> x y distance (10) kernel_size (31) smoothing_algorithm(MedianBlur) - one of: 'Blur, MedianBlur, GaussianBlur, BilateralFilter'\n");
        return -1;
    }
    
    std::string filepath = std::string(argv[1]);
    size_t dotpos = filepath.find_last_of(".");
    std::string basename;
    std::string ext;
    if (dotpos != std::string::npos) {
        basename = filepath.substr(0, dotpos);
        ext  = filepath.substr(dotpos, filepath.size() - dotpos);
    } else {
        basename = filepath;
        ext  = "";
    }
    Mat image = imread(filepath, CV_LOAD_IMAGE_COLOR);
    
    if (!image.data) {
        printf("Invalid image: %s\n", filepath.c_str());
        return -1;
    }
    
    int x = atoi(argv[2]);
    int y = atoi(argv[3]);
    int hue = 0;
    int distance = (argc>=5?atoi(argv[4]):10);
    int kernel_size = (argc>=6?atoi(argv[5]):31);       // default, works best on test4, use 5 for test3
    cv::Size s = image.size();
    int rows = s.height;
    int cols = s.width;
    unsigned long image_size = rows * cols;
    
    if (x < 0 || x > cols || y < 0 || y > rows) {
        printf("Invalid x,y coordinates: must be in range 0-%d, 0-%d\n", rows, cols);
        return -1;
    }
    ImageAnalysisService::smoothing_type smoothing = ImageAnalysisService::MedianBlur;
    if (argc >= 7) {
        if (!strcmp(argv[6], "Blur")) {
            smoothing = ImageAnalysisService::Blur;
        } else if (!strcmp(argv[6], "MedianBlur")) {
            smoothing = ImageAnalysisService::MedianBlur;
        } else if (!strcmp(argv[6], "GaussianBlur")) {
            smoothing = ImageAnalysisService::GaussianBlur;
        } else if (!strcmp(argv[6], "BilateralFilter")) {
            smoothing = ImageAnalysisService::BilateralFilter;
        } else {
            printf("Invalid smoothing filter: must be one of: Blur, MedianBlur, GaussianBlur, BilateralFilter\n");
            return -1;
        }
        std::cout << "Using " << argv[6] << " smoothing" << std::endl;
    } else {
        std::cout << "Using MedianBlur smoothing" << std::endl;
    }
    cvtColor(image, image, COLOR_BGR2RGB);  // opencv reads BGR, we use RGB
    
    try {
        ImageAnalysisService *service = new ImageAnalysisService;
        
        std::string outfilename = basename+std::string("_out")+ext;
        service->DISPLAY_IMAGE(image, filepath);
        service->SAVE_IMAGE(image, outfilename);
        
        std::vector<cv::Point> region = service->FIND_REGION(image, x, y, distance, &hue);
        
        std::cout << "Image size  " << rows << " x " << cols << " = " <<  image_size << " pixels" << std::endl;
        std::cout << "Found " << region.size() << " pixels of color " << hue << " within range " << distance << " about " << (((float)region.size()*100.0)/(float)image_size) << "%" << std::endl;
        
        std::string regionfilename = basename+std::string("_region")+ext;
        service->DISPLAY_PIXELS(region, "region");
        service->SAVE_PIXELS(region, regionfilename);
        
        std::vector<cv::Point> perimeter = service->FIND_PERIMETER(region);
        
        std::cout << "Found " << perimeter.size() << " perimeter pixels" << std::endl;
        
        std::string perimeterfilename = basename+std::string("_perimeter")+ext;
        service->DISPLAY_PIXELS(perimeter, "perimeter");
        service->SAVE_PIXELS(perimeter, perimeterfilename);
        
        // best results so far:
        std::vector<cv::Point> smooth_perimeter = service->FIND_SMOOTH_PERIMETER(region, smoothing, distance, kernel_size);
        
        std::cout << "Found " << smooth_perimeter.size() << " smoothed perimeter pixels" << std::endl;
        
        std::string smoothperimeterfilename = basename+std::string("_smooth_perimeter")+ext;
        service->DISPLAY_PIXELS(smooth_perimeter, "smooth perimeter");
        service->SAVE_PIXELS(smooth_perimeter, smoothperimeterfilename);
        
        delete service;
    } catch (char const *message) {
        std::cerr << message << std::endl;
    } catch (Exception e) {
    std::cerr << e.what() << std::endl;
    }
    
    return 0;
}
