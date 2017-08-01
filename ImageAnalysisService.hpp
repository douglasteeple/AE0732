/*
 * Class ImageAnalysisService - performs various image analysis services.
 *
 *  Created by Douglas Teeple on 7/31/17.
 *  Copyright © 2017 Douglas Teeple. All rights reserved.
 *
 */

class ImageAnalysisService {

private:
    /*
     * Find the outer bounds of points in a vector of points.
     */
    bool FIND_REGION_SIZE(const std::vector<cv::Point> &region, int *rows, int *cols) {
        if (rows == NULL || cols == NULL) {
            return false;
        }
        *rows = 0;
        *cols = 0;
        // find the dimensions of the region
        for (int i=0; i<region.size(); i++) {
            if (region[i].y > *rows)
                *rows = region[i].y;
            if (region[i].x > *cols)
                *cols = region[i].x;
        }
        (*rows)++;
        (*cols)++;
        return (*rows > 0 && *cols > 0);
    }
    
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
    
    std::vector<cv::Point> FIND_REGION(const cv::Mat &image, int x, int y, int distance=10, int *hue=NULL);
    
    /*
     *  FIND_PERIMETER accepts the output of FIND_REGION and outputs contiguous pixels that
     *  border the region. These pixels should be a subset of pixels returned by FIND_REGION.
     */
    
    std::vector<cv::Point> FIND_PERIMETER(const std::vector<cv::Point> &region);
    
    /*
     *  FIND_SMOOTH_PERIMETER takes the output of FIND_REGION and returns a smoothed perimeter of a given region.
     *  Ideal smoothing:
     *      - removes jagged contours, small artifacts, etc.
     *      - remains generally close to the non-smoothed original boundary
     *      - potentially  expressed via a lower degree parametric representation of the smoothed perimeter, 
     *        such as splines or bezier curves.
     *  Just for concreteness: curve fitting, interpolation, gaussian smoothing, spline curves, and Catmull-Rom 
     *  are all examples of the kinds of smoothing that might be done.
     */
    std::vector<cv::Point> FIND_SMOOTH_PERIMETER(const std::vector<cv::Point> &region);
    
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
     *  SAVE_PIXELS accepts the vector output from FIND_* and saves the image to a file.
     */
    void SAVE_PIXELS(const std::vector<cv::Point> &region, std::string const &file_name);
    
    /*
     *  SAVE_IMAGE saves the image to a file.
     */
    void SAVE_IMAGE(const cv::Mat &image, std::string const &file_name);
    
    
};
