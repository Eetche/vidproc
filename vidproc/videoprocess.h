#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <algorithm>

#pragma once


class Videoprocess
{
private:
    std::vector<cv::Point> darkpixels;
    int resizeW;
    int resizeH;
public:
    void video2bin(std::string, std::string);
    std::vector<cv::Point> getdarkpixs(const cv::Mat&);
    void tosymb(std::vector<cv::Point>);

    Videoprocess();
};