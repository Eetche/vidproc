#include <iostream>
#include <opencv2/opencv.hpp>
#include "videoprocess.h"

int main()
{  
    Videoprocess vidproc;

    cv::Mat img = cv::imread("C:/Users/user/Desktop/projects/tosymb/image.jpg");

    std::vector<cv::Point> darkpixels = vidproc.getdarkpixs(img);

    vidproc.tosymb(darkpixels);

    return 0;
}