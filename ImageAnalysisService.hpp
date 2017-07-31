/*
 * Class ImageAnalysisService - performs various image analysis services.
 *
 *  Created by Douglas Teeple on 7/31/17.
 *  Copyright © 2017 Douglas Teeple. All rights reserved.
 *
*/

class ImageAnalysisService {
    
    public:
    
    /*
     *  FIND_REGION accepts an RGB image, an (X, Y) pixel location, and a distance parameter to
     *  control a greedy style algorithm that "flood fills" the nearby pixels in order to find
     *  a contiguous patch of pixels that are similar in color. The return value is a vector of
     *  cv::Points. The RGB image is converted to HSV to easily select by color (H). The maximum
     *  distance from the color at point x,y is given as a parameter. The hue at the x,y point
     *  is optionally returned in the "*hue" argument. Returns empty vector if x or y outside
     *  image range.
     */
    
    std::vector<cv::Point> FIND_REGION(const cv::Mat &image, int x, int y, int distance=10, int *hue=nullptr);
    
    /*
     *  FIND_PERIMETER accepts the output of FIND_REGION and outputs contiguous pixels that
     *  border the region. These pixels should be a subset of pixels returned by FIND_REGION.
     */
    
    std::vector<cv::Point> FIND_PERIMETER(const std::vector<cv::Point> &region);
    
    /*
     *  DISPLAY_IMAGE provides a method for displaying loaded RGB images.
     */
    void DISPLAY_IMAGE(const cv::Mat &image, std::string const &win_name);
    
    /*
     *  DISPLAY_PIXELS provides a method for displaying an image representation of the 
     *  results from the above FIND_* operators.
     */
    void DISPLAY_PIXELS(const std::vector<cv::Point> &region, std::string const &win_name);
    
    /*
     *  SAVE_PIXELS accepts the output from FIND_* and saves the image to a file.
     */
    void SAVE_PIXELS(const std::vector<cv::Point> &region, std::string const &file_name);
    
    /*
     *  SAVE_IMAGE saves the image to a file.
     */
    void SAVE_IMAGE(const cv::Mat &image, std::string const &file_name);
    

};
