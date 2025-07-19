#include <iostream>
#include <opencv2/opencv.hpp>
#include "vidproc/videoprocess.h"

int main()
{  
    cv::Mat img = cv::imread("image.jpg");

    Videoprocess::tosymb(img);

    return 0;
}